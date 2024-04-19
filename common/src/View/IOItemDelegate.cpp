//
// Created by ennis on 12/04/24.
//

#include "IOItemDelegate.h"

namespace TrenchBroom
{
namespace View
{
IOItemDelegate::IOItemDelegate(
  IOTable* table,
  const IOPropertyModel* model,
  const QSortFilterProxyModel* proxyModel,
  QWidget* parent)
  : QStyledItemDelegate{parent}
  , m_table{table}
  , m_model{model}
  , m_proxyModel{proxyModel}
{
}
QWidget* IOItemDelegate::createEditor(
  QWidget* parent, const QStyleOptionViewItem& option, const QModelIndex& index) const
{
  return QStyledItemDelegate::createEditor(parent, option, index);
}
void IOItemDelegate::setEditorData(QWidget* editor, const QModelIndex& index) const
{
  QStyledItemDelegate::setEditorData(editor, index);
}

} // namespace View
} // namespace TrenchBroom