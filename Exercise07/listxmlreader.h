#ifndef LISTXMLREADER_H
#define LISTXMLREADER_H

#include <QString>
class Customer;

class ListXmlReader
{
public:
    ListXmlReader();
    QList<Customer*> read(QString fileName = "customers.xml") const;
};

#endif // LISTXMLREADER_H
