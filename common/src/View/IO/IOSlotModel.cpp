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

namespace TrenchBroom {
namespace View {
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

const std::vector<SlotRow>& IOSlotModel::rows() const
{
  return m_rows;
}

void IOSlotModel::setRows(const std::vector<SlotRow>& rows)
{
  m_rows = rows;
}

SlotModelFilter IOSlotModel::filter() const
{
  return m_filter;
}

void IOSlotModel::setFilter(const SlotModelFilter filter)
{
  m_filter = filter;
}
} // View
} // TrenchBroom