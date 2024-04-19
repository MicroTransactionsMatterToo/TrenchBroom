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
#include "NotifierConnection.h"


namespace TrenchBroom
{
class NotifierConnection;
}
namespace TrenchBroom::View
{
class IOConnectionTable;
}
class QSortFilterProxyModel;
namespace TrenchBroom::View
{
class IOConnectionModel;
}
namespace TrenchBroom::View
{
class MapDocument;
}
namespace TrenchBroom
{
namespace View
{

class IOConnectionGrid : public QWidget
{
  Q_OBJECT
private:
  std::weak_ptr<MapDocument> m_document;

  IOConnectionModel* m_model;
  QSortFilterProxyModel* m_proxyModel;
  IOConnectionTable* m_table;

  NotifierConnection m_notifierConnection;

public:
  explicit IOConnectionGrid(
    std::weak_ptr<MapDocument> document, QWidget* parent = nullptr);
};

} // namespace View
} // namespace TrenchBroom
