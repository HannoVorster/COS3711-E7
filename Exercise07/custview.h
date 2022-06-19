#ifndef CUSTVIEW_H
#define CUSTVIEW_H

#include <QWidget>
class CustomerList;
class QPushButton;
class QTableView;
class CustomerTableModel;

class CustView : public QWidget
{
    Q_OBJECT
public:
    explicit CustView(QWidget *parent = nullptr);
    void readList();
    void writeList();

public slots:
    void addCustomer();

signals:
    void statusChanged(QString status);

private:
    void setupGUI();
    CustomerTableModel *model;
    QTableView *view;
    QPushButton *btnAddCust;
    //QPushButton *btnExit;
};

#endif // CUSTVIEW_H
