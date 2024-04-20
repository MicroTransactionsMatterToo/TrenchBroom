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

#pragma once
#include <QAbstractTableModel>

#include "Assets/PropertyDefinition.h"


namespace TrenchBroom
{
namespace Model
{
class EntityNodeBase;
}

namespace View
{
class MapDocument;

enum class SlotDirection
{
  Unset,
  Input,
  Output
};

using SlotParamType = Assets::IOType;

class SlotRow final
{
private:
  std::string m_key;
  SlotDirection m_direction;
  SlotParamType m_paramType;

  std::string m_tooltip;

public:
  SlotRow(
    std::string key,
    SlotDirection direction,
    SlotParamType paramType,
    std::string tooltip);

  const std::string& key() const;
  SlotDirection direction() const;
  SlotParamType paramType() const;
  const std::string& tooltip() const;

  static SlotRow rowForIODef(
    const std::shared_ptr<Assets::OutputPropertyDefinition>& definition);
  static SlotRow rowForIODef(
    const std::shared_ptr<Assets::InputPropertyDefinition>& definition);
  static std::vector<SlotRow> rowsForEntityNode(const Model::EntityNodeBase* node);
};

/**
 * Model for IOSlotGrid, representing the input/output definitions in the FGD file
 */
class IOSlotModel : public QAbstractTableModel
{
  Q_OBJECT
public:
  static constexpr int NumColumns = 4;
  enum
  {
    ColumnDirection,
    ColumnSlotName,
    ColumnParamType,
    ColumnDescription
  };

private:
  std::vector<SlotRow> m_rows;
  std::weak_ptr<MapDocument> m_document;
  SlotDirection m_filter;

public:
  explicit IOSlotModel(std::weak_ptr<MapDocument> document, QObject* parent);

  const std::vector<SlotRow>& rows() const;
  void setRows(const std::vector<SlotRow>& rows);

  SlotDirection filter() const;
  void setFilter(SlotDirection filter);

  int rowCount(const QModelIndex& parent) const override;
  int columnCount(const QModelIndex& parent) const override;
  QVariant data(const QModelIndex& index, int role) const override;

  QVariant headerData(int section, Qt::Orientation orientation, int role) const override;

public slots:
  void updateFromMapDocument();
};

} // namespace View
} // namespace TrenchBroom
