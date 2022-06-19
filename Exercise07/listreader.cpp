#include "listreader.h"
#include "filereader.h"
#include "customer.h"
#include <QStringList>
#include <QString>
#include <QVariant>

#include <QDebug>

ListReader::ListReader()
{
}

QList<Customer*> ListReader::read(QString fileName) const
{
    // Read Customer data from file
    FileReader fr(fileName);
    QString inStr(fr.read().trimmed());

    // Instantiate and populate customer list
    QList<Customer*> cl;

    // Split input string into separate lines
    QStringList inData(inStr.split("\n"));
    QStringList line;

    // Instantiate and populate Customer objects
    for (int count = 0; count < inData.size(); count++) {

        // Split each line QString to QStringList
        line = inData.at(count).split("#");

        // Using fixed properties
        Customer *cust(new Customer);
        cust->setProperty("title", line.at(0));
        cust->setProperty("name", line.at(1));
        cust->setProperty("address", line.at(2).split("*"));
        cust->setProperty("postCode", line.at(3));
        cust->setProperty("code", line.at(4));
        cust->setProperty("balance", line.at(5).toDouble());

/*      // Using parametized constructor
        Customer *cust(new Customer(line.at(0),
                                    line.at(1),
                                    line.at(2).split("*"),
                                    line.at(3),
                                    line.at(4),
                                    line.at(5).toDouble()));
*/
        cl.append(cust);
    }

    return cl;
}
