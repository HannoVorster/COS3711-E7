#include "customerclient.h"
#include "custview.h"
#include <QMenuBar>
#include <QStatusBar>
#include <QToolBar>
#include <QCloseEvent>
#include <QMessageBox>

CustomerClient::CustomerClient(QWidget *parent)
    : QMainWindow{parent}
{
    setupGui();
    setupMenuBar();
    setupStatusBar();
    setupToolBar();

    setWindowTitle("Customer Client");
    setWindowState(Qt::WindowMaximized);
}

void CustomerClient::setupGui()
{
    custView = new CustView();
    setCentralWidget(custView);
    custView->readList();
}

void CustomerClient::setupMenuBar()
{
    menuBar = new QMenuBar();
    menuBar->addMenu("File");
    menuBar->addMenu("Edit");
    menuBar->addMenu("View");
    menuBar->addMenu("Report");
    menuBar->addMenu("Help");

    setMenuBar(menuBar);
}

void CustomerClient::setupStatusBar()
{
    statusBar()->showMessage(tr("Ready"), 3000);
}

void CustomerClient::setupToolBar()
{
    toolBar = new QToolBar();

    actOpen = new QAction(QIcon(":/Images/open.png"), "Open");
    toolBar->addAction(actOpen);

    actSave = new QAction(QIcon(":/Images/save.png"), "Save");
    toolBar->addAction(actSave);

    actAdd = new QAction(QIcon(":/Images/add.png"), "Add");
    toolBar->addAction(actAdd);

    addToolBar(toolBar);
}

void CustomerClient::showStatus(QString status)
{
    statusBar()->showMessage(status, 3000);
}

void CustomerClient::closeEvent(QCloseEvent *event)
{
    int response;
    response = QMessageBox::warning(this, "Exit", "Are you sure you want to Exit ?",
                                    QMessageBox::Yes | QMessageBox::No);
    if (response == QMessageBox::Yes) {
        custView->writeList();
        event->accept();
    }
    else {
        event->ignore();
    }
}
