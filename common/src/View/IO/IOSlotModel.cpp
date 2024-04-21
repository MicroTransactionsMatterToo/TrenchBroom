/*
 *
 *  Copyright (C) 2024 Ennis Massey
 *
 *  This file is part of TrenchBroom.
 *
 *  TrenchBroom is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  TrenchBroom is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with TrenchBroom. If not, see <http://www.gnu.org/licenses/>.
 *
 */

//
// Created by ennis on 19/04/24.
//

#include "IOSlotModel.h"

#include <QtDebug>

#include "Assets/EntityDefinition.h"
#include "IO/ResourceUtils.h"
#include "Macros.h"
#include "Model/EntityNodeBase.h"
#include "View/MapDocument.h"
#include "View/QtUtils.h"

#include "kdl/memory_utils.h"

#include <utility>

#define MODEL_LOG(x)

namespace TrenchBroom
{
namespace View
{

SlotRow::SlotRow(
  std::string key,
  const SlotDirection direction,
  const SlotParamType paramType,
  std::string tooltip)
  : m_key{std::move(key)}
  , m_direction{direction}
  , m_paramType{paramType}
  , m_tooltip{std::move(tooltip)}
{
}

const std::string& SlotRow::key() const
{
  return m_key;
}

SlotDirection SlotRow::direction() const
{
  return m_direction;
}

SlotParamType SlotRow::paramType() const
{
  return m_paramType;
}

const std::string& SlotRow::tooltip() const
{
  return m_tooltip;
}

SlotRow SlotRow::rowForIODef(
  const std::shared_ptr<Assets::InputPropertyDefinition>& definition)
{
  return SlotRow{
    definition->key(),
    SlotDirection::Input,
    definition->ioType().value_or(SlotParamType::Unknown),
    definition->shortDescription()};
}


SlotRow SlotRow::rowForIODef(
  const std::shared_ptr<Assets::OutputPropertyDefinition>& definition)
{
  return SlotRow{
    definition->key(),
    SlotDirection::Output,
    definition->ioType().value_or(SlotParamType::Unknown),
    definition->shortDescription()};
}


std::vector<SlotRow> SlotRow::rowsForEntityNode(const Model::EntityNodeBase* node)
{
  auto result = std::vector<SlotRow>{};

  if (node->entity().definition() == nullptr)
  {
    return {};
  }

  for (auto nodeIOdefs = node->entity().definition()->ioDefinitions();
       const auto& definition : nodeIOdefs)
  {
    if (definition->type() == Assets::PropertyDefinitionType::InputProperty)
    {
      const auto& inputDef =
        std::static_pointer_cast<Assets::InputPropertyDefinition>(definition);
      result.push_back(rowForIODef(inputDef));
    }
    if (definition->type() == Assets::PropertyDefinitionType::OutputProperty)
    {
      const auto& outputDef =
        std::static_pointer_cast<Assets::OutputPropertyDefinition>(definition);
      result.push_back(rowForIODef(outputDef));
    }
  }

  return result;
}

IOSlotModel::IOSlotModel(std::weak_ptr<MapDocument> document, QObject* parent)
  : QAbstractTableModel{parent}
  , m_document{std::move(document)}
  , m_filter{SlotDirection::Unset}
{
  updateFromMapDocument();
}

const std::vector<SlotRow>& IOSlotModel::rows() const
{
  return m_rows;
}

void IOSlotModel::setRows(const std::vector<SlotRow>& rows)
{
  beginResetModel();
  m_rows = rows;
  endResetModel();
}

SlotDirection IOSlotModel::filter() const
{
  return m_filter;
}

void IOSlotModel::setFilter(const SlotDirection filter)
{
  m_filter = filter;
}

void IOSlotModel::updateFromMapDocument()
{
  qDebug() << "IOSlotModel::updateFromMapDocument()";

  const auto document = kdl::mem_lock(m_document);

  const auto entityNodes = document->allSelectedEntityNodes();
  // We don't handle multiple entities slots at the moment, maybe in future
  if (entityNodes.size() > 1 || entityNodes.empty())
  {
    qDebug() << "IOSlotModel::updateFromMapDocument() ignore multi-select";
    setRows({});
    return;
  }
  auto rows = SlotRow::rowsForEntityNode(entityNodes.front());
  std::erase_if(rows, [this](const SlotRow& item) {
    return filter() == SlotDirection::Unset ? false : item.direction() == filter();
  });
  setRows(rows);
}

int IOSlotModel::rowCount(const QModelIndex& parent) const
{
  if (parent.isValid())
  {
    return 0;
  }
  return static_cast<int>(m_rows.size());
}
int IOSlotModel::columnCount(const QModelIndex& parent) const
{
  if (parent.isValid())
  {
    return 0;
  }
  return NumColumns;
}
QVariant IOSlotModel::data(const QModelIndex& index, int role) const
{
  if (
    !index.isValid()
    || (index.row() < 0 || index.row() >= static_cast<int>(m_rows.size()))
    || (index.column() < 0 || index.column() >= NumColumns))
  {
    return QVariant{};
  }

  auto document = kdl::mem_lock(m_document);
  const auto& row = m_rows.at(static_cast<size_t>(index.row()));

  switch (role)
  {
  case Qt::DecorationRole: {
    if (index.column() == ColumnDirection)
    {
      if (row.direction() == SlotDirection::Output)
      {
        return QVariant{IO::loadSVGIcon("Locked_small.svg")};
      }
      if (row.direction() == SlotDirection::Input)
      {
        return QVariant{IO::loadSVGIcon("Protected_small.svg")};
      }
    }
    break;
  }
  case Qt::DisplayRole:
    switchFallthrough();
  case Qt::EditRole: {
    switch (index.column())
    {
    case ColumnSlotName:
      return QVariant{mapStringToUnicode(document->encoding(), row.key())};
    case ColumnParamType: {
      return QVariant{
        mapStringToUnicode(document->encoding(), Assets::IOTypeMap.at(row.paramType()))};
    }
    case ColumnDescription:
      return QVariant{mapStringToUnicode(document->encoding(), row.tooltip())};
    }
    break;
  }
  case Qt::ToolTipRole: {
    if (!row.tooltip().empty())
    {
      return QVariant{mapStringToUnicode(document->encoding(), row.tooltip())};
    }
  }
  default:
    return QVariant{};
  }

  return QVariant{};
}

QVariant IOSlotModel::headerData(int section, Qt::Orientation orientation, int role) const
{
  if (orientation == Qt::Vertical || role != Qt::DisplayRole)
  {
    return QVariant{};
  }

  switch (section)
  {
  case ColumnSlotName:
    return QVariant{tr("Name")};
  case ColumnDirection:
    return QVariant{tr("Dir")};
  case ColumnParamType:
    return QVariant{tr("Param. Type")};
  case ColumnDescription:
    return QVariant{tr("Desc.")};
  default:
    return QVariant{"UNKNOWN"};
  }
}


} // namespace View
} // namespace TrenchBroom