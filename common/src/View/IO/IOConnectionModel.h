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

#ifndef IOCONNECTIONMODEL_H
#define IOCONNECTIONMODEL_H
#include <QAbstractTableModel>

namespace TrenchBroom::View
{
class MapDocument;
}
namespace TrenchBroom::Model
{
class IOLink;
}
namespace TrenchBroom
{
namespace View
{

enum class ConnectionDirection
{
  Input,
  Output
};

enum class ConnectionParamType
{
  Void,
  String,
  Float,
  Integer,
  Bool
};

class ConnectionRow
{
private:
  std::string m_signalName;
  std::string m_targetName;
  std::string m_targetInput;
  float m_refireCount;
  float m_fireDelay;
  QVariant m_parameterValue;

  ConnectionDirection m_direction;
  ConnectionParamType m_paramType;

public:
  ConnectionRow();
  ConnectionRow(const Model::IOLink* link);

  const std::string& signalName() const;
  const std::string& targetName() const;
  const std::string& targetInput() const;
  float refireCount() const;
  float fireDelay() const;
  const QVariant& parameterValue() const;
  ConnectionDirection direction() const;
  ConnectionParamType paramType() const;
};

class IOConnectionModel : public QAbstractTableModel
{
  Q_OBJECT

private:
  std::vector<ConnectionRow> m_rows;
  std::weak_ptr<MapDocument> m_document;

public:
  explicit IOConnectionModel(std::weak_ptr<MapDocument> document, QObject* parent);

public:
  int rowCount(const QModelIndex& parent) const override;
  int columnCount(const QModelIndex& parent) const override;
  QVariant data(const QModelIndex& index, int role) const override;
  bool setData(const QModelIndex& index, const QVariant& value, int role) override;
  QVariant headerData(int section, Qt::Orientation orientation, int role) const override;
  Qt::ItemFlags flags(const QModelIndex& index) const override;
};

} // namespace View
} // namespace TrenchBroom

#endif // IOCONNECTIONMODEL_H
