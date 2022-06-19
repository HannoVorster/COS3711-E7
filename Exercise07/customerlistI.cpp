#include "customerlistI.h"

#include <QDebug>

CustomerList::CustomerList()
{
}

CustomerList::~CustomerList()
{
    qDeleteAll(*this);
}

void CustomerList::clear()
{
    qDeleteAll(*this);

    for (int count = 0; count < this->size(); count++) {
        removeAt(count);
    }
}

QList<Customer*>* CustomerList::getList() const
{
    QList<Customer*> *list(new QList<Customer*>);

    for (int count = 0; count < this->size(); count++) {
/*
        // Hard copy - if required to make an independent list
        Customer *newCust = new Customer(this->at(count)->getTitle(),
                                         this->at(count)->getName(),
                                         this->at(count)->getAddress(),
                                         this->at(count)->getPostCode(),
                                         this->at(count)->getCode(),
                                         this->at(count)->getBalance());
        list.append(newCust);
*/
        list->append(this->at(count));
    }

    return list;
}

QString CustomerList::toString() const
{
    QString outStr;

    for (int count = 0; count < this->size(); count++) {
        outStr += this->at(count)->toString() + "\n\n";
    }

    return outStr;
}
