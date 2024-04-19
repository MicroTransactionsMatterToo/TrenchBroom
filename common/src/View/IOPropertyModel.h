/*
Copyright (C) 2024 Ennis Massey

 This file is part of TrenchBroom.

 TrenchBroom is free software: you can redistribute it and/or modify
 it under the terms of the GNU General Public License as published by
 the Free Software Foundation, either version 3 of the License, or
 (at your option) any later version.

 TrenchBroom is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU General Public License for more details.

 You should have received a copy of the GNU General Public License
 along with TrenchBroom. If not, see <http://www.gnu.org/licenses/>.
 */

#pragma once

#include <QAbstractTableModel>

#include "kdl/reflection_decl.h"

#include <map>
#include <memory>
#include <string>
#include <tuple>
#include <vector>

namespace TrenchBroom
{
namespace Model
{
class EntityNodeBase;
} // namespace Model
namespace View
{

class MapDocument;
using IOParameter = std::variant<int, float, std::string, std::nullptr_t>;

class IOOutputRow
{
private:
  int m_key;
  std::string m_ioName;
  std::string m_ioTargetEntity;
  std::string m_ioTargetInput;
  IOParameter m_ioParameterValue;
  float m_ioDelay;
  float m_ioRefires;

  std::string m_tooltip;

public:
  IOOutputRow();
  IOOutputRow(int key, const Model::EntityNodeBase* node);

  const std::string& key() const;
  std::string ioName() const;
  std::string ioTargetEntity() const;
  std::string ioTargetInput() const;
  IOParameter ioParameterValue() const;
  float ioDelay() const;
  float ioRefires() const;

  const std::string& tooltip() const;

  std::shared_ptr<Model::EntityNodeBase> getIOTarget();
};

enum class IOTypeFilter
{
  All,
  OutputsOnly,
  InputsOnly
};

enum class IOParameterType
{
  Void,
  Float,
  String,
  Integer,
  Boolean
};

class IOPropertyModel : public QAbstractTableModel
{
  Q_OBJECT
public:
  static const int NumColumns = 6;
private:
  std::vector<IOOutputRow> m_outputRows;
  IOTypeFilter m_typeFilter;
  IOParameterType m_parameterType;
  std::weak_ptr<MapDocument> m_document;

public:
  explicit IOPropertyModel(std::weak_ptr<MapDocument> document, QObject* parent);



public: // QAbstractTableModel overrides
  int rowCount(const QModelIndex& parent) const override;
  int columnCount(const QModelIndex& parent) const override;
  Qt::ItemFlags flags(const QModelIndex& index) const override;
  QVariant data(const QModelIndex& index, int role) const override;
  bool setData(const QModelIndex& index, const QVariant& value, int role) override;
  QVariant headerData(int section, Qt::Orientation orientation, int role) const override;
};
} // namespace View
} // namespace TrenchBroom
