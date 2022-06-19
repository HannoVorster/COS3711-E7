#ifndef CUSTOMERLISTC_H
#define CUSTOMERLISTC_H

/**************************
 * CustomerList implemented using composition
 *************************/
#include "customer.h"

class CustomerList
{
public:
    CustomerList();
    ~CustomerList();
    void append(Customer *c);
    void clear();
    QList<Customer*>* getList() const;
    QString toString() const;

private:
    QList<Customer*> *list;
};

#endif // CUSTOMERLISTC_H
