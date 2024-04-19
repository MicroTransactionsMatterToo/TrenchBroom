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

#include "IOConnectionModel.h"

namespace TrenchBroom
{
namespace View
{
const std::string& ConnectionRow::signalName() const
{
  return m_signalName;
}
const std::string& ConnectionRow::targetName() const
{
  return m_targetName;
}
const std::string& ConnectionRow::targetInput() const
{
  return m_targetInput;
}
float ConnectionRow::refireCount() const
{
  return m_refireCount;
}
float ConnectionRow::fireDelay() const
{
  return m_fireDelay;
}
const QVariant& ConnectionRow::parameterValue() const
{
  return m_parameterValue;
}
ConnectionDirection ConnectionRow::direction() const
{
  return m_direction;
}
ConnectionParamType ConnectionRow::paramType() const
{
  return m_paramType;
}
} // namespace View
} // namespace TrenchBroom