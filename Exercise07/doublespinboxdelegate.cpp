#include "doublespinboxdelegate.h"
#include <QDoubleSpinBox>

DoubleSpinBoxDelegate::DoubleSpinBoxDelegate(QObject *parent)
    : QStyledItemDelegate(parent)
{
}

QWidget* DoubleSpinBoxDelegate::createEditor(QWidget *parent, const QStyleOptionViewItem &option,
                      const QModelIndex &index) const
{
    // Returns the editor widget - QDoubleSpinBox
    Q_UNUSED(index);

    QDoubleSpinBox *editor = new QDoubleSpinBox(parent);
    editor->setFrame(false);
    editor->setMinimum(0);
    editor->setMaximum(9999.99);
    editor->setDecimals(2);
    editor->setAlignment(Qt::AlignRight);
    editor->setButtonSymbols(QAbstractSpinBox::NoButtons);

    return editor;
}

void DoubleSpinBoxDelegate::setEditorData(QWidget *editor, const QModelIndex &index) const
{
    // Reads data from model, converts to double, writes data to editor widget
    double value = index.model()->data(index, Qt::EditRole).toDouble();

    QDoubleSpinBox *spnEditor = static_cast<QDoubleSpinBox*>(editor);
    spnEditor->setValue(value);
}

void DoubleSpinBoxDelegate::setModelData(QWidget *editor, QAbstractItemModel *model,
                  const QModelIndex &index) const
{
    // Reads content of spinbox editor, writes data to model
    QDoubleSpinBox *spnEditor = static_cast<QDoubleSpinBox*>(editor);
    double value = spnEditor->value();

    model->setData(index, value, Qt::EditRole);
}

void DoubleSpinBoxDelegate::updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option,
                          const QModelIndex &index) const
{
    // Updates editor geometry, to fill cell in view
    Q_UNUSED(index)

    editor->setGeometry(option.rect);
}
