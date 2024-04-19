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
#include "NotifierConnection.h"


class QSortFilterProxyModel;

namespace TrenchBroom
{
namespace View
{
class IOTable;
class IOPropertyModel;
class MapDocument;


/**
 * Browser for an entities IO slots
 */
class IOBrowser : public QWidget
{
  Q_OBJECT
private:
  std::weak_ptr<MapDocument> m_document;
  IOPropertyModel* m_model;
  QSortFilterProxyModel* m_proxyModel;
  IOTable* m_table;

  NotifierConnection m_notifierConnection;

public:
  explicit IOBrowser(std::weak_ptr<MapDocument> document, QWidget* parent = nullptr);

private:
  void createGui(std::weak_ptr<MapDocument> document);
};

} // namespace View
} // namespace TrenchBroom
