#ifndef LISTREADER_H
#define LISTREADER_H

#include <QString>
class Customer;

class ListReader
{
public:
    ListReader();
    QList<Customer*> read(QString fileName = "customers.txt") const;
};

#endif // LISTREADER_H
