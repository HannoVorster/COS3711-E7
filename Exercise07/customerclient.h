#ifndef CUSTOMERCLIENT_H
#define CUSTOMERCLIENT_H

#include <QMainWindow>

class QMenuBar;
#include "custview.h"

class CustomerClient : public QMainWindow
{
    Q_OBJECT
public:
    explicit CustomerClient(QWidget *parent = nullptr);
    void closeEvent(QCloseEvent *event);

private:
    void setupMenuBar();
    void setupStatusBar();
    void setupToolBar();
    void setupGui();
    CustView* custView;
    QMenuBar* menuBar;
    QToolBar* toolBar;
    QAction* actOpen;
    QAction* actSave;
    QAction* actAdd;

private slots:
    void showStatus(QString status);
    //void openFile();
    //void saveFile();

signals:


};

#endif // CUSTOMERCLIENT_H
