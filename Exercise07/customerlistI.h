#ifndef CUSTOMERLISTI_H
#define CUSTOMERLISTI_H

/****************************
 * CustomerList implmented using inheritance
 ***************************/

#include "customer.h"
#include <QList>

class CustomerList : public QList<Customer*>
{
public:
    CustomerList();
    ~CustomerList();
    void clear();
    QList<Customer*>* getList() const;
    QString toString() const;

};

#endif // CUSTOMERLISTI_H
