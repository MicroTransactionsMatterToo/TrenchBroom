//
// Created by ennis on 12/04/24.
//

#pragma once
#include <QStyledItemDelegate>


class QSortFilterProxyModel;
namespace TrenchBroom
{
namespace View
{
class IOPropertyModel;
class IOTable;

class IOItemDelegate : public QStyledItemDelegate
{
  Q_OBJECT
private:
  IOTable* m_table;
  const IOPropertyModel* m_model;
  const QSortFilterProxyModel* m_proxyModel;

public:
  IOItemDelegate(
    IOTable* table,
    const IOPropertyModel* model,
    const QSortFilterProxyModel* proxyModel,
    QWidget* parent = nullptr);

  QWidget* createEditor(
    QWidget* parent,
    const QStyleOptionViewItem& option,
    const QModelIndex& index) const override;
  void setEditorData(QWidget* editor, const QModelIndex& index) const override;
};

} // namespace View
} // namespace TrenchBroom
