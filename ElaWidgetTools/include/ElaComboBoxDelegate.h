#ifndef ELACOMBOBOXDELEGATE_H
#define ELACOMBOBOXDELEGATE_H

#include <QStyledItemDelegate>

#include "stdafx.h"

class ELA_EXPORT ElaComboBoxDelegate : public QStyledItemDelegate
{
public:
    explicit ElaComboBoxDelegate(QObject *parent = nullptr);
    explicit ElaComboBoxDelegate(const QStringList& texts, QObject* parent = nullptr);

    QWidget* createEditor(QWidget* parent, const QStyleOptionViewItem& option, const QModelIndex& index) const override;
    void setEditorData(QWidget* editor, const QModelIndex& index) const override;
    void setModelData(QWidget* editor, QAbstractItemModel* model, const QModelIndex& index) const override;

    void addItem(const QString& selectText);
    void addItems(const QStringList& selectTexts);

private:
    QStringList m_SelecterTexts;
};

#endif // ELACOMBOBOXDELEGATE_H
