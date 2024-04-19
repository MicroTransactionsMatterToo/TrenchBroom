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


namespace TrenchBroom::View
{
class MapDocument;
}

namespace TrenchBroom
{
namespace Model
{
class EntityNodeBase;
}

namespace View
{

enum class SlotDirection
{
  Input,
  Output
};

enum class SlotParamType
{
  Void,
  String,
  Float,
  Integer,
  Bool
};

enum class SlotModelFilter
{
  All,
  Output,
  Input
};

class SlotRow
{
private:
  std::string m_key;
  SlotDirection m_direction;
  SlotParamType m_paramType;

  std::string m_tooltip;

public:
  SlotRow();
  SlotRow(std::string key, const Model::EntityNodeBase* node);

  const std::string& key() const;
  SlotDirection direction() const;
  SlotParamType paramType() const;
  const std::string& tooltip() const;
};

/**
 * Model for IOSlotGrid, representing the input/output definitions in the FGD file
 */
class IOSlotModel : public QAbstractTableModel
{
  Q_OBJECT
private:
  std::vector<SlotRow> m_rows;
  std::weak_ptr<MapDocument> m_document;
  SlotModelFilter m_filter;

public:
  explicit IOSlotModel(std::weak_ptr<MapDocument> document, QObject* parent);

  const std::vector<SlotRow>& rows() const;
  void setRows(const std::vector<SlotRow>& rows);

  SlotModelFilter filter() const;
  void setFilter(SlotModelFilter filter);

};

} // namespace View
} // namespace TrenchBroom

