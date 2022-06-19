#include "listxmlwriter.h"
#include "filewriter.h"
#include <QMetaProperty>
#include <QDebug>
#include <QDomDocument>

ListXmlWriter::ListXmlWriter(CustomerTableModel *model)
    : ctm(model)
{
}

bool ListXmlWriter::write(QString fileName)
{
    //QString address, outStr;

    // Create DOM & root...
    QDomDocument doc;
    QDomElement rootElement;
    rootElement = doc.createElement("customers");
    doc.appendChild(rootElement);

    // Using model
    for (int row = 0; row < ctm->rowCount(QModelIndex()); row++) {

        QDomElement customer = doc.createElement("customer");
        customer.setAttribute("type", "Customer");

        QDomElement title = doc.createElement("title");
        QDomText titleText = doc.createTextNode(ctm->data(ctm->index(row, 0), Qt::DisplayRole).toString());

        QDomElement name = doc.createElement("name");
        QDomText nameText = doc.createTextNode(ctm->data(ctm->index(row, 1), Qt::DisplayRole).toString());

        QDomElement address = doc.createElement("address");

        QDomElement street = doc.createElement("street");
        QDomText streetText = doc.createTextNode(ctm->data(ctm->index(row,2), Qt::DisplayRole).toString());

        QDomElement suburb = doc.createElement("suburb");
        QDomText suburbText = doc.createTextNode(ctm->data(ctm->index(row,3), Qt::DisplayRole).toString());

        QDomElement town = doc.createElement("town");
        QDomText townText = doc.createTextNode(ctm->data(ctm->index(row,4), Qt::DisplayRole).toString());

        QDomElement province = doc.createElement("province");
        QDomText provinceText = doc.createTextNode(ctm->data(ctm->index(row,5), Qt::DisplayRole).toString());

        QDomElement postCode = doc.createElement("postcode");
        QDomText postCodeText = doc.createTextNode(ctm->data(ctm->index(row,6), Qt::DisplayRole).toString());

        QDomElement code = doc.createElement("code");
        QDomText codeText = doc.createTextNode(ctm->data(ctm->index(row,7), Qt::DisplayRole).toString());

        QDomElement balance = doc.createElement("balance");
        QDomText balanceText = doc.createTextNode(ctm->data(ctm->index(row,8), Qt::DisplayRole).toString());

        // Append all elements...
        rootElement.appendChild(customer);

        customer.appendChild(title);
        title.appendChild(titleText);

        customer.appendChild(name);
        name.appendChild(nameText);

        customer.appendChild(address);
        address.appendChild(street);
        street.appendChild(streetText);
        address.appendChild(suburb);
        suburb.appendChild(suburbText);
        address.appendChild(town);
        town.appendChild(townText);
        address.appendChild(province);
        province.appendChild(provinceText);

        customer.appendChild(postCode);
        postCode.appendChild(postCodeText);

        customer.appendChild(code);
        code.appendChild(codeText);

        customer.appendChild(balance);
        balance.appendChild(balanceText);

        /*address = QString("%1*%2*%3*%4")
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
                      .arg(ctm->data(ctm->index(row,8), Qt::DisplayRole).toDouble()));*/
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
    if (!fw.write(doc.toString())) {
        return false;
    }

    return true;
}
