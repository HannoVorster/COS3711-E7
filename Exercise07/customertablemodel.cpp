#include "customertablemodel.h"
#include <QColor>
#include <QDebug>

CustomerTableModel::CustomerTableModel()
{
}

CustomerTableModel::~CustomerTableModel()
{
    qDeleteAll(customerList);
}

int CustomerTableModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return customerList.size();
}

int CustomerTableModel::columnCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return 9;
}

QVariant CustomerTableModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid()) {
        return QVariant();
    }

    int col = index.column();
    int row = index.row();

    if (role == Qt::TextAlignmentRole) {

        switch(index.column()) {
            // Title
            case 0:
                return int(Qt::AlignLeft | Qt::AlignVCenter);
                break;
            // Name
            case 1:
                return int(Qt::AlignLeft | Qt::AlignVCenter);
                break;
            // Address1 - Street address
            case 2:
                return int(Qt::AlignLeft | Qt::AlignVCenter);
                break;
            // Address2 - Suburb
            case 3:
                return int(Qt::AlignLeft | Qt::AlignVCenter);
                break;
            // Address4 - Town / City
            case 4:
                return int(Qt::AlignLeft | Qt::AlignVCenter);
                break;
            // Address5 - Province
            case 5:
                return int(Qt::AlignLeft | Qt::AlignVCenter);
                break;
            // Post code
            case 6:
                return int(Qt::AlignLeft | Qt::AlignVCenter);
                break;
            // Customer code
            case 7:
                return int(Qt::AlignLeft | Qt::AlignVCenter);
                break;
            // Balance
            case 8:
                return int(Qt::AlignRight | Qt::AlignVCenter);
                break;
            default:
                return int(Qt::AlignLeft | Qt::AlignVCenter);
        }
    }

    if (role == Qt::DisplayRole || role == Qt::EditRole) {

        switch(col) {
            case 0:
                return customerList.at(row)->getTitle();
                break;
            case 1:
                return customerList.at(row)->getName();
                break;
            case 2:
                return customerList.at(row)->getAddress().at(0);
                break;
            case 3:
                return customerList.at(row)->getAddress().at(1);
                break;
            case 4:
                return customerList.at(row)->getAddress().at(2);
                break;
            case 5:
                return customerList.at(row)->getAddress().at(3);
                break;
            case 6:
                return customerList.at(row)->getPostCode();
                break;
            case 7:
                return customerList.at(row)->getCode();
                break;
            case 8:
                return QString::number(customerList.at(row)->getBalance(), 'f', 2);
                break;
        }
    }

    if (role == Qt::BackgroundRole) {

         if (index.column() == 8) {

             if (customerList.at(row)->getBalance() >= 5000) {
                 return QVariant(QColor(Qt::red));
             }
         }
    }

    return QVariant();
}

QVariant CustomerTableModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role != Qt::DisplayRole) {
        return QVariant();
    }

    if (orientation == Qt::Vertical) {
        return QVariant();
    }

    switch (section) {
        case 0:
            return QString("Title");
            break;
        case 1:
            return QString ("Name");
            break;
        case 2:
            return QString ("Street address");
            break;
        case 3:
            return QString ("Suburb");
            break;
        case 4:
            return QString ("Town / City");
            break;
        case 5:
            return QString ("Province");
            break;
        case 6:
            return QString ("Post code");
            break;
        case 7:
            return QString ("Code");
            break;
        case 8:
            return QString ("Balance");
            break;
        default:
            return QVariant();
    }

    return QVariant();
}

bool CustomerTableModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if (index.isValid()) {
        int col = index.column();
        int row = index.row();

        if (role == Qt::EditRole) {
            QStringList address;
            address = customerList.at(row)->getAddress();

            switch(col) {
                case 0:
                    customerList.at(row)->setTitle(value.toString());
                    break;
                case 1:
                    customerList.at(row)->setName(value.toString());
                    break;
                case 2:
                    address.replace(0, value.toString());
                    customerList.at(row)->setAddress(address);
                    break;
                case 3:
                    address.replace(1, value.toString());
                    customerList.at(row)->setAddress(address);
                    break;
                case 4:
                    address.replace(2, value.toString());
                    customerList.at(row)->setAddress(address);
                    break;
                case 5:
                    address.replace(3, value.toString());
                    customerList.at(row)->setAddress(address);
                    break;
                case 6:
                    customerList.at(row)->setPostCode(value.toString());
                    break;
                case 7:
                    customerList.at(row)->setCode(value.toString());
                    break;
                case 8:
                    customerList.at(row)->setBalance(value.toDouble());
                    break;
                default:
                    return false;
            }
        }

        emit dataChanged(index, index);
        return true;
    }

    return false;
}

Qt::ItemFlags CustomerTableModel::flags(const QModelIndex &index) const
{
    if (index.isValid()) {
        return (Qt::ItemIsEnabled | Qt::ItemIsSelectable | Qt::ItemIsEditable);
    }
    else {
        return Qt::NoItemFlags;
    }
}

void CustomerTableModel::addCustomer(Customer *cust)
{
    int row = customerList.size();
    beginInsertRows(QModelIndex(), row+1, row+1);
    customerList.append(cust);
    endInsertRows();
}

void CustomerTableModel::clear()
{
    int row = customerList.size();
    beginRemoveRows(QModelIndex(), 0, row-1);
    qDeleteAll(customerList);
    customerList.clear();
    endRemoveRows();

}
