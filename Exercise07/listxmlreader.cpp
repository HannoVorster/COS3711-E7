#include "listxmlreader.h"
#include "filereader.h"
#include "customer.h"
#include <QStringList>
#include <QString>
#include <QVariant>
#include <QXmlStreamReader>
#include <QFile>

#include <QDebug>

ListXmlReader::ListXmlReader()
{
}

QList<Customer*> ListXmlReader::read(QString fileName) const
{
    fileName = "customers.xml";
    // Read Customer data from file
    //FileReader fr(fileName);
    QString title;
    QString name;
    QString address;
    QString street;
    QString suburb;
    QString town;
    QString province;
    QString postCode;
    QString code;
    QString balance;

    QList<Customer*> cl;

    QFile file(fileName);
    QXmlStreamReader reader;

    if (!file.open(QIODevice::ReadOnly)) {
        qDebug() << "Error opening file: " << file.errorString();
        exit(0);
    }

    reader.setDevice(&file);
    reader.readNext();

    while (!reader.atEnd()) {
        if (reader.isStartElement()) {
            if (reader.name().toString() == "title") {
                title = reader.readElementText();
            }
            else if (reader.name().toString() == "name") {
                name = reader.readElementText();
            }
            else if (reader.name().toString() == "postcode") {
                postCode = reader.readElementText();
            }
            else if (reader.name().toString() == "street") {
                address = reader.readElementText();
            }
            else if (reader.name().toString() == "suburb") {
                address = address + "*" + reader.readElementText();
            }
            else if (reader.name().toString() == "town") {
                address = address + "*" + reader.readElementText();
            }
            else if (reader.name().toString() == "province") {
                address = address + "*" + reader.readElementText();
            }
            else if (reader.name().toString() == "code") {
                code = reader.readElementText();
            }
            else if (reader.name().toString() == "balance") {
                balance = reader.readElementText();
            }
        }

        if (reader.isEndElement() && reader.name().toString() == "customer") {
            Customer *cust(new Customer);
            cust->setProperty("title", title);
            cust->setProperty("name", name);
            cust->setProperty("address", address.split("*"));
            cust->setProperty("postCode", postCode);
            cust->setProperty("code", code);
            cust->setProperty("balance", balance.toDouble());

            cl.append(cust);
        }

        reader.readNext();
    }

    file.close();
    return cl;
}
