#include "ElaComboBoxDelegate.h"

#include "ElaComboBox.h"

ElaComboBoxDelegate::ElaComboBoxDelegate(QObject *parent)
    : QStyledItemDelegate{parent}
{}

ElaComboBoxDelegate::ElaComboBoxDelegate(const QStringList &texts, QObject *parent):QStyledItemDelegate{parent},
    m_SelecterTexts(texts)
{

}

QWidget *ElaComboBoxDelegate::createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    Q_UNUSED(option)
    Q_UNUSED(index)
    ElaComboBox* editor = new ElaComboBox(parent);
    editor->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Expanding);
    editor->addItems(m_SelecterTexts);
    return editor;
}

void ElaComboBoxDelegate::setEditorData(QWidget *editor, const QModelIndex &index) const
{
    ElaComboBox* comboBox = static_cast<ElaComboBox*>(editor);
    comboBox->setCurrentText(index.data().toString());
}

void ElaComboBoxDelegate::setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const
{
    ElaComboBox* comboBox = static_cast<ElaComboBox*>(editor);
    model->setData(index, comboBox->currentText());
}

void ElaComboBoxDelegate::addItem(const QString &selectText)
{
    m_SelecterTexts.append(selectText);
}

void ElaComboBoxDelegate::addItems(const QStringList &selectTexts)
{
    m_SelecterTexts.append(selectTexts);
}
