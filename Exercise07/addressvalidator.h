#ifndef ADDRESSVALIDATOR_H
#define ADDRESSVALIDATOR_H

#include <QObject>
#include <QTextEdit>
#include <QRegularExpression>

class AddressValidator : public QObject
{
    Q_OBJECT
public:
    explicit AddressValidator(QTextEdit *qte, QObject *parent = nullptr);
    enum State{Invalid, Intermediate, Acceptable};
    bool hasAcceptableInput() const;
    QString getRegex1() const;
    bool setRegex1(QString re);
    QString getRegex2() const;
    bool setRegex2(QString re);
    QString getRegex3() const;
    bool setRegex3(QString re);
    QString getRegex4() const;
    bool setRegex4(QString re);

public slots:
    void validate();

signals:
    void addressValidated();

private:
    void deleteLastChar();
    QTextEdit *textEdit;
    State state;
    int numberOfRows;
    QRegularExpression regex1;
    QRegularExpression regex2;
    QRegularExpression regex3;
    QRegularExpression regex4;

    State line1State;
    State line2State;
    State line3State;
    State line4State;

    int line1MaxLen;
    int line2MaxLen;
    int line3MaxLen;

    QStringList provinces;
    QStringList provinces2;
    QString provinces1;
};

#endif // ADDRESSVALIDATOR_H
