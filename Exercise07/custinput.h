#ifndef CUSTINPUT_H
#define CUSTINPUT_H

#include <QDialog>
#include <QObject>

class QPushButton;
class QLineEdit;
class QTextEdit;
class QComboBox;
class QDoubleSpinBox;
class Customer;
class AddressValidator;

class CustInput : public QDialog
{
    Q_OBJECT
public:
    CustInput();
    ~CustInput();
    Customer* getCustomer() const;

private slots:
    void checkInputs();
    void processInput();

private:
    void setupGUI();
    Customer *customer;

    AddressValidator *valAddress;

    QComboBox *cmbTitle;
    QLineEdit *edtName;
    QTextEdit *txtAddress;
    QLineEdit *edtPostCode;
    QLineEdit *edtCode;
    QDoubleSpinBox *spnBalance;

    QPushButton *btnSubmit;
    QPushButton *btnClose;
};

#endif // CUSTINPUT_H
