//
// Created by ennis on 11/04/24.
//

#include "IOPropertyModel.h"

namespace TrenchBroom::View
{
IOOutputRow::IOOutputRow() {}
IOOutputRow::IOOutputRow(int key, const Model::EntityNodeBase* node)
{}
const std::string& IOOutputRow::key() const {}
std::string IOOutputRow::ioName() const {}
std::string IOOutputRow::ioTargetEntity() const {}
std::string IOOutputRow::ioTargetInput() const {}
IOParameter IOOutputRow::ioParameterValue() const {}
float IOOutputRow::ioDelay() const {}
float IOOutputRow::ioRefires() const {}
const std::string& IOOutputRow::tooltip() const {}
std::shared_ptr<Model::EntityNodeBase> IOOutputRow::getIOTarget() {}

IOPropertyModel::IOPropertyModel(std::weak_ptr<MapDocument> document, QObject* parent)
  : QAbstractTableModel{parent}
  , m_document{document}
{

}
int IOPropertyModel::rowCount(const QModelIndex& parent) const
{
  if (parent.isValid())
  {
    return 0;
  }
  return static_cast<int>(m_outputRows.size());
}
int IOPropertyModel::columnCount(const QModelIndex& parent) const
{
  if (parent.isValid())
  {
    return 0;
  }
  return NumColumns;
}
Qt::ItemFlags IOPropertyModel::flags(const QModelIndex& index) const
{
  return QAbstractTableModel::flags(index);
}
QVariant IOPropertyModel::data(const QModelIndex& index, int role) const
{
  return QVariant{};
}
bool IOPropertyModel::setData(const QModelIndex& index, const QVariant& value, int role)
{
  return QAbstractTableModel::setData(index, value, role);
}
QVariant IOPropertyModel::headerData(
  int section, Qt::Orientation orientation, int role) const
{
  return QAbstractTableModel::headerData(section, orientation, role);
}
} // namespace TrenchBroom::View