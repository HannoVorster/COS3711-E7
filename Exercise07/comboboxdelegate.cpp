#include "comboboxdelegate.h"
#include <QComboBox>
#include <QStringList>

ComboboxDelegate::ComboboxDelegate(QObject *parent)
    : QStyledItemDelegate(parent)
{
}

QWidget* ComboboxDelegate::createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    Q_UNUSED(option)
    Q_UNUSED(index)

    // Create a QComboBox, and populate it
    QComboBox *cmb = new QComboBox(parent);

    QStringList list;
    list << "EC" << "FS" << "GAU" << "KZN" << "LIM" << "MPU" << "NC" << "NW" << "WC";
    cmb->addItems(list);

    return cmb;
}

void ComboboxDelegate::setEditorData(QWidget *editor, const QModelIndex &index) const
{
    // Cast QWidget to QComboBox, and check that it is valid
    QComboBox *cmb = static_cast<QComboBox *>(editor);
    Q_ASSERT(cmb);

    // Get current cell data
    const QString curText = index.model()->data(index, Qt::EditRole).toString();

    // Find index of current data in QComboBox
    const int cmbIndex = cmb->findText(curText);

    // Set index of QComboBox to current data
    if (cmbIndex > 0) {
        cmb->setCurrentIndex(cmbIndex);
    }
}

void ComboboxDelegate::setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const
{
    // Cast QWidget to QComboBox, and check that it is valid
    QComboBox *cmb = static_cast<QComboBox *>(editor);
    Q_ASSERT(cmb);

    // Set current cell data to QComboBox current text
    model->setData(index, cmb->currentText(), Qt::EditRole);
}
