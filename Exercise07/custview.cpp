#include "custview.h"
#include "custinput.h"
#include "listxmlwriter.h"
#include "listreader.h"
#include "listxmlreader.h"
#include "customertablemodel.h"
#include "comboboxdelegate.h"
#include "doublespinboxdelegate.h"
#include <QTableView>
#include <QPushButton>
#include <QVBoxLayout>
#include <QCloseEvent>
#include <QMessageBox>
#include <QTextStream>
#include <QAction>
//#include <QList>

CustView::CustView(QWidget *parent)
    : QWidget(parent),
      model(new CustomerTableModel),
      view(new QTableView),
      btnAddCust(new QPushButton("Add customer"))
{
    // SetupGUI
    setupGUI();

    // Connect Signals and Slots
    connect(btnAddCust, SIGNAL(clicked()), this, SLOT(addCustomer()));
}

void CustView::addCustomer()
{
    CustInput newCust;
    QTextStream cout(stdout);

    newCust.exec();

    if (newCust.result() == QDialog::Accepted) {
        model->addCustomer(newCust.getCustomer());
    }
    else {
        cout << "Dialog closed - No data available" << Qt::endl;
    }
}

void CustView::readList()
{
    // Create list to hold customer objects
    QList<Customer*> list;
    ListXmlReader lr;
    list = lr.read();

    // Clear model before adding customers
    model->clear();

    foreach (Customer* cust, list) {
        model->addCustomer(cust);
    }

    view->resizeColumnsToContents();

    QTextStream cout(stdout);
    cout << "Customer list read from XML file" << Qt::endl;
}

void CustView::writeList()
{
    QString prompt("Customer list written to XML file");

    ListXmlWriter lw(model);
    if (!lw.write()) {
        prompt = "Error: Customer list not written to XML file";
    }

    QTextStream cout(stdout);
    cout << prompt << Qt::endl;
}

void CustView::setupGUI()
{
    // Setup layout
    QVBoxLayout *layout(new QVBoxLayout(this));
    layout->addWidget(view);
    layout->addWidget(btnAddCust);

    // Initialize widgets
    view->resizeColumnsToContents();
    view->setModel(model);

    // Set delegates
    ComboboxDelegate *cmbDel(new ComboboxDelegate(this));
    view->setItemDelegateForColumn(5, cmbDel);

    DoubleSpinBoxDelegate *spnDel(new DoubleSpinBoxDelegate(this));
    view->setItemDelegateForColumn(8, spnDel);
}
