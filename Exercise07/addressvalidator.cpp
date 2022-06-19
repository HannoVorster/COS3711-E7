#include "addressvalidator.h"
#include "custinput.h"
#include <QRegularExpressionMatch>

#include <QDebug>

AddressValidator::AddressValidator(QTextEdit *qte, QObject *parent)
    :  QObject(parent),
      textEdit(qte),
      state(Invalid),
      numberOfRows(4),
      regex1("(([1-9]\\d{1,3})( ))?[a-zA-Z ]*"),
      regex2("[a-zA-Z ]*"),
      regex3("[a-zA-Z ]*"),
      regex4("^(EC|FS|GAU|KZN|LIM|MPU|NC|NW|WC)$"),
      line1State(Invalid),
      line2State(Invalid),
      line3State(Invalid),
      line4State(Invalid),
      line1MaxLen(30),     // Maximum number of chars per line
      line2MaxLen(25),
      line3MaxLen(25),
      provinces({"EC","FS","GAU","KZN","LIM","MPU","NC","NW","WC"}),
      provinces2({"GA","KZ","LI","MP"}),
      provinces1("EFGKLMNW")
{ }

void AddressValidator::validate()
{
    QStringList list;
    QString inStr(textEdit->toPlainText());

    // Check if there is more than one line in address
    if (inStr.contains("\n")) {
        list = inStr.split("\n");
    }
    else {
        list.append(inStr.trimmed());
    }
    int numFields = list.size();

    // Check number of fields / rows
    if (numFields > numberOfRows) {
        while (numFields > numberOfRows) {
            list.removeLast();
            numFields--;
        }

        // Remove excess row from textEdit
        textEdit->undo();
    }
/*
    // Check rows - Regular expressions
    // 4th row - Province
    // This should work, but doesn't
    // hasPartialMatch() never returns true
    if (numFields > 3) {

        if (list.at(3).length() > 0) {
            // Only check if there is actual content
            QRegularExpressionMatch match = regex4.match(list.at(3), QRegularExpression::PartialPreferCompleteMatch);

            if (match.hasMatch()) {
                line4State = Acceptable;
                qDebug() << "Fourth row: " << "Acceptable" << Qt::endl;

            }
            else if (match.hasPartialMatch()) {
                line4State = Intermediate;
                qDebug() << "Fourth row: " << "Intermediate" << Qt::endl;

            }
            else {
                deleteLastChar();
                qDebug() << "Fourth row: " << "Invalid" << Qt::endl;
            }
        }
    }
*/

    // 4th row alternate method
    if (numFields > 3) {

        if (list.at(3).length() > 0) {
            // Only check if there is actual content

            switch(list.at(3).length()) {
                case 1:
                    // Contains first letter of any province
                    if (provinces1.contains(list.at(3))) {
                        line4State = Intermediate;
                    }
                    else {
                        // Invalid
                        // State stays same as before
                        deleteLastChar();
                    }
                    break;
                case 2:
                    // Contains 2 char province
                    if (provinces.contains(list.at(3))) {
                        line4State = Acceptable;
                    }
                    else if (provinces2.contains(list.at(3))) {
                        // First 2 chars of 3 char provinces
                        line4State = Intermediate;
                    }
                    else {
                        // Invalid
                        // State stays same as before
                        deleteLastChar();
                    }
                    break;
                case 3:
                    // Contains 3 char province
                    if (provinces.contains(list.at(3))) {
                        line4State = Acceptable;
                    }
                    else {
                        // Invalid
                        // State stays same as before
                        deleteLastChar();
                    }
                    break;
                default:
                    // Invalid
                    // State stays same as before
                    deleteLastChar();
            }
        }
    }

    // 3rd row - Town / City
    if (numFields > 2) {

        if (list.at(2).length() > 0) {
            // Only test if has actual content
            QRegularExpressionMatch match = regex3.match(list.at(2));

            if (match.hasMatch() && list.at(2).length() <= line3MaxLen) {
                if (list.at(2).length() < 3) {
                   // Must be at least 3 char
                   line3State = Intermediate;
                }
                else {
                    line3State = Acceptable;
                }
                qDebug() << "Third row: " << "Acceptable" << Qt::endl;

            }
            else if (match.hasPartialMatch() && list.at(2).length() <= line3MaxLen) {
                line3State = Intermediate;
                qDebug() << "Third row: " << "Intermediate" << Qt::endl;
            }
            else {
                // Invalid
                // State stays same as before
                deleteLastChar();
                qDebug() << "Third row: " << "Delete char" << Qt::endl;
            }
        }
    }

    // 2nd row - Suburb
    if (numFields > 1) {

        if (list.at(1).length() > 0) {
            // Only check if there is actual content
            QRegularExpressionMatch match = regex2.match(list.at(1));

            if (match.hasMatch() && list.at(1).length() <= line2MaxLen) {
                if (list.at(1).length() < 3) {
                   // Must be at least 3 char
                   line2State = Intermediate;
                }
                else {
                    line2State = Acceptable;
                }
                qDebug() << "Second row: " << "Acceptable" << Qt::endl;
            }
            else if (match.hasPartialMatch() && list.at(1).length() <= line2MaxLen) {
                line2State = Intermediate;
                qDebug() << "Second row: " << "Intermediate" << Qt::endl;
            }
            else {
                // State stays same as before
                deleteLastChar();
                qDebug() << "Second row: " << "Delete char" << Qt::endl;
            }
        }
    }

    // 1st row - Street address
    if (numFields > 0) {

        if (list.at(0).length() > 0) {
            // Only check if there is actual content
            QRegularExpressionMatch match = regex1.match(list.at(0));

            qDebug() << "List at 0: " << list.at(0) << Qt::endl;
            qDebug() << "Has Match: " << match.hasMatch() << Qt::endl;
            qDebug() << "List At 0 Length: " << list.at(0).length() << Qt::endl;
            qDebug() << "Line1MaxLength: " << line1MaxLen << Qt::endl;

            if (match.hasMatch() && list.at(0).length() <= line1MaxLen ) {
                if (list.at(0).length() < 3) {
                   // Must be at least 3 char
                   line1State = Intermediate;
                }
                else {
                    line1State = Acceptable;
                }
                qDebug() << "First row: " << "Acceptable" << Qt::endl;
            }
            else if (match.hasPartialMatch() && list.at(0).length() <= line1MaxLen) {
                line1State = Intermediate;
                qDebug() << "First row: " << "Intermediate" << Qt::endl;
            }
            else {
                // State stays same as before
                deleteLastChar();
                qDebug() << "First row: " << "Delete char" << Qt::endl;
            }
        }
    }

    // Set state to lowest state of any individual input
    state = qMin(line1State, line2State);
    state = qMin(state, line3State);
    state = qMin(state, line4State);

    emit addressValidated();
}

QString AddressValidator::getRegex1() const
{
    return regex1.pattern();
}

bool AddressValidator::setRegex1(QString re)
{
    QString existPattern(regex1.pattern());
    regex1.setPattern(re);

    if (regex1.isValid()) {
        return true;
    }
    else {
        regex1.setPattern(existPattern);
    }

    return false;
}

QString AddressValidator::getRegex2() const
{
    return regex2.pattern();
}

bool AddressValidator::setRegex2(QString re)
{
    QString existPattern(regex2.pattern());
    regex2.setPattern(re);

    if (regex2.isValid()) {
        return true;
    }
    else {
        regex2.setPattern(existPattern);
    }

    return false;
}

QString AddressValidator::getRegex3() const
{
    return regex3.pattern();
}

bool AddressValidator::setRegex3(QString re)
{
    QString existPattern(regex3.pattern());
    regex3.setPattern(re);

    if (regex3.isValid()) {
        return true;
    }
    else {
        regex3.setPattern(existPattern);
    }

    return false;
}

QString AddressValidator::getRegex4() const
{
    return regex4.pattern();
}

bool AddressValidator::setRegex4(QString re)
{
    QString existPattern(regex4.pattern());
    regex4.setPattern(re);

    if (regex4.isValid()) {
        return true;
    }
    else {
        regex4.setPattern(existPattern);
    }

    return false;
}

bool AddressValidator::hasAcceptableInput() const
{
    if (state == Acceptable) {
        return true;
    }

    return false;
}

void AddressValidator::deleteLastChar()
{
    // Block signal to prevent textChanged() signal from being emitted
    textEdit->blockSignals(true);
    textEdit->textCursor().deletePreviousChar();
    textEdit->blockSignals(false);
}
