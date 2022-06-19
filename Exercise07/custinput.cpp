#include "custinput.h"
#include "customer.h"
#include "addressvalidator.h"

#include <QVBoxLayout>
#include <QPushButton>
#include <QTextEdit>
#include <QLineEdit>
#include <QComboBox>
#include <QDoubleSpinBox>
#include <QLabel>

CustInput::CustInput()
    : customer(new Customer),
      cmbTitle(new QComboBox),
      edtName(new QLineEdit),
      txtAddress(new QTextEdit),
      edtPostCode(new QLineEdit),
      edtCode(new QLineEdit),
      spnBalance(new QDoubleSpinBox),
      btnSubmit(new QPushButton("Submit")),
      btnClose(new QPushButton("Close"))
{
    valAddress = new AddressValidator(txtAddress);

    // Setup GUI
    setupGUI();

    // Connect Signals and Slots
    connect(btnSubmit, &QPushButton::clicked, this, &CustInput::processInput);
    connect(btnSubmit, &QPushButton::clicked, this, &CustInput::accept);
    connect(btnClose, &QPushButton::clicked, this, &CustInput::reject);
    connect(btnClose, &QPushButton::clicked, this, &QWidget::close);
    connect(edtName, &QLineEdit::textChanged, this, &CustInput::checkInputs);
    connect(edtPostCode, &QLineEdit::textChanged, this, &CustInput::checkInputs);
    connect(edtCode, &QLineEdit::textChanged, this, &CustInput::checkInputs);
    connect(txtAddress, &QTextEdit::textChanged, valAddress, &AddressValidator::validate);
    connect(valAddress, &AddressValidator::addressValidated, this, &CustInput::checkInputs);

    // Setup window
    setWindowTitle("Add customer");
}

CustInput::~CustInput()
{
}

void CustInput::checkInputs()
{
    if (edtName->hasAcceptableInput() && edtPostCode->hasAcceptableInput() && edtCode->hasAcceptableInput() && valAddress->hasAcceptableInput()) {
        btnSubmit->setDisabled(false);
    }
    else {
        btnSubmit->setDisabled(true);
    }
}

void CustInput::processInput()
{
    customer->setTitle(cmbTitle->currentText());
    customer->setName(edtName->text());
    customer->setAddress(txtAddress->toPlainText().split("\n"));
    customer->setPostCode(edtPostCode->text());
    customer->setCode(edtCode->text());
    customer->setBalance(spnBalance->value());

    txtAddress->append(customer->toString());
}

Customer* CustInput::getCustomer() const
{
    return customer;
}

void CustInput::setupGUI()
{
    // Declare widgets
    QVBoxLayout *layout(new QVBoxLayout(this));
    QLabel *lblTitle(new QLabel("Title"));
    QLabel *lblName(new QLabel("Name"));
    QLabel *lblAddress(new QLabel("Address"));
    QLabel *lblPostCode(new QLabel("Postcode"));
    QLabel *lblCode(new QLabel("Customer code"));
    QLabel *lblBalance(new QLabel("Balance"));

    // Setup layout
    layout->addWidget(lblTitle);
    layout->addWidget(cmbTitle);
    layout->addWidget(lblName);
    layout->addWidget(edtName);
    layout->addWidget(lblAddress);
    layout->addWidget(txtAddress);
    layout->addWidget(lblPostCode);
    layout->addWidget(edtPostCode);
    layout->addWidget(lblCode);
    layout->addWidget(edtCode);
    layout->addWidget(lblBalance);
    layout->addWidget(spnBalance);
    layout->addSpacing(10);
    layout->addWidget(btnSubmit);
    layout->addWidget(btnClose);

    // Initialize widgets
    QStringList list = QStringList() << "Mr" << "Mrs" << "Ms" << "Dr" << "Hon" << "Rev";
    cmbTitle->addItems(list);

    edtName->setMaxLength(25);

    spnBalance->setMaximum(9999.99);
    spnBalance->setMinimum(0.00);
    spnBalance->setDecimals(2);
    spnBalance->setAlignment(Qt::AlignRight);
    spnBalance->setButtonSymbols(QAbstractSpinBox::NoButtons);

    // Tooltips...
    cmbTitle->setToolTip("Select from the list");
    edtName->setToolTip("Enter name & surname");
    txtAddress->setToolTip("All four lines are required");
    edtPostCode->setToolTip("Enter the 4 digit code");
    edtCode->setToolTip("Enter customer code");
    spnBalance->setToolTip("Enter balance in rands");

    // Place holders...
    edtName->setPlaceholderText("John Snow");
    txtAddress->setPlaceholderText("23 Beukes Street\nThe Reeds\nCenturion\nGAU");
    edtPostCode->setPlaceholderText("0123");
    edtCode->setPlaceholderText("ABC123");

    // Validators...
    QRegularExpression rxName("^[a-zA-Z ]{3,}$");
    QValidator *valName = new QRegularExpressionValidator(rxName, this);
    edtName->setValidator(valName);

    QRegularExpression rxPostCode("^[1-9]{4}$");
    QValidator *valPostCode = new QRegularExpressionValidator(rxPostCode, this);
    edtPostCode->setValidator(valPostCode);

    QRegularExpression rxCode("^([A-Z]{2})20([0-9][0-9])(EC|WC|KZN|GAU)[a-j](?!\d*00$)([0-9][0-9])$");
    QValidator *valCode = new QRegularExpressionValidator(rxCode, this);
    edtCode->setValidator(valCode);

    // Button disabled...
    btnSubmit->setDisabled(true);
}
