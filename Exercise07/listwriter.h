#ifndef LISTWRITER_H
#define LISTWRITER_H

#include <QString>
#include "customertablemodel.h"
//class CustomerTableModel;

class ListWriter
{
public:
    ListWriter(CustomerTableModel *model);
    bool write(QString fileName = "customers.txt");

private:
    CustomerTableModel *ctm;
};

#endif // LISTWRITER_H
