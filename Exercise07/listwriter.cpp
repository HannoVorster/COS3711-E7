#include "listwriter.h"
#include "filewriter.h"
#include <QMetaProperty>
#include <QDebug>

ListWriter::ListWriter(CustomerTableModel *model)
    : ctm(model)
{
}

bool ListWriter::write(QString fileName)
{
    QString address, outStr;

    // Using model
    for (int row = 0; row < ctm->rowCount(QModelIndex()); row++) {

        address = QString("%1*%2*%3*%4")
                .arg(ctm->data(ctm->index(row,2), Qt::DisplayRole).toString())
                .arg(ctm->data(ctm->index(row,3), Qt::DisplayRole).toString())
                .arg(ctm->data(ctm->index(row,4), Qt::DisplayRole).toString())
                .arg(ctm->data(ctm->index(row,5), Qt::DisplayRole).toString());

        outStr.append(QString("%1#%2#%3#%4#%5#%6\n")
                      .arg(ctm->data(ctm->index(row,0), Qt::DisplayRole).toString())
                      .arg(ctm->data(ctm->index(row,1), Qt::DisplayRole).toString())
                      .arg(address)
                      .arg(ctm->data(ctm->index(row,6), Qt::DisplayRole).toString())
                      .arg(ctm->data(ctm->index(row,7), Qt::DisplayRole).toString())
                      .arg(ctm->data(ctm->index(row,8), Qt::DisplayRole).toDouble()));
    }

/*
    QString outStr, lineStr, valStr;

    // Using QMetaObject
    const QMetaObject *meta;
    int numProperties;
    QMetaProperty metaProp;

    foreach(Customer *cust, *list->getList()) {
        meta = cust->metaObject();
        numProperties = meta->propertyCount();

        // Start from 1, omit objectName property
        for (int count = 1; count < numProperties; count++) {
            metaProp = meta->property(count);
            const char *name = metaProp.name();
            QVariant value = cust->property(name);

            //qDebug() << "write()  name " << name << Qt::endl;
            if (strcmp(name, "address") == 0) {
                valStr = value.toStringList().join("*");
            }
            else {
                valStr = value.toString();
            }

            lineStr.append(valStr);
            lineStr.append("#");
        }

        // Remove last #
        lineStr.chop(1);
        // Add newline
        lineStr.append("\n");

        outStr.append(lineStr);
    }
*/
/*  // Using getters()
    foreach(Customer *cust, list->getList()) {
        outStr.append(QString("%1#%2#%3#%4#%5#%6\n")
                      .arg(cust->getTitle())
                      .arg(cust->getName())
                      .arg(cust->getAddress().join("*"))
                      .arg(cust->getPostCode())
                      .arg(cust->getCode())
                      .arg(QString::number(cust->getBalance(), 'f', 2)));  // Convert double
    }
*/

    FileWriter fw(fileName);
    if (!fw.write(outStr)) {
        return false;
    }

    return true;
}
