#ifndef LISTXMLWRITER_H
#define LISTXMLWRITER_H

#include <QString>
#include "customertablemodel.h"
//class CustomerTableModel;

class ListXmlWriter
{
public:
    ListXmlWriter(CustomerTableModel *model);
    bool write(QString fileName = "customers.xml");

private:
    CustomerTableModel *ctm;
};

#endif // LISTXMLWRITER_H
