#include <QApplication>
#include "customerclient.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    CustomerClient view;
    view.show();

    return a.exec();
}
