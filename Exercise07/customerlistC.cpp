#include "customerlistC.h"

CustomerList::CustomerList()
    : list(new QList<Customer*>)
{
}

CustomerList::~CustomerList()
{
    qDeleteAll(*list);
}

void CustomerList::append(Customer *c)
{
    list->append(c);
}

void CustomerList::clear()
{
    qDeleteAll(*list);
    list->clear();
}

QList<Customer*>* CustomerList::getList() const
{
    return list;
}

QString CustomerList::toString() const
{
    QString outStr;

    foreach (Customer *cust, *list) {
        outStr += cust->toString() + "\n\n";
    }

    return outStr;
}
