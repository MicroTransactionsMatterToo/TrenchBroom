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

#pragma once
#include "NotifierConnection.h"


namespace TrenchBroom::View
{
class Selection;
}
namespace TrenchBroom::Model
{
class Node;
}
class QSortFilterProxyModel;
namespace TrenchBroom::View
{
class IOSlotTable;
}
namespace TrenchBroom::View
{
class IOSlotModel;
}
namespace TrenchBroom
{
namespace View
{
class MapDocument;
enum class SlotDirection;

class IOSlotGrid : public QWidget
{
  Q_OBJECT
private:
  std::weak_ptr<MapDocument> m_document;

  IOSlotModel* m_model;
  QSortFilterProxyModel* m_proxyModel;
  IOSlotTable* m_table;

  NotifierConnection m_notifierConnection;

public:
  explicit IOSlotGrid(
    const std::weak_ptr<MapDocument>& document, QWidget* parent = nullptr);

  void setFilter(SlotDirection filter) const;

private:
  void createGui(const std::weak_ptr<MapDocument>& document);

private: // Notification Handlers
  void connectObservers();

  void documentWasNewed(MapDocument* document);
  void documentWasLoaded(MapDocument* document);
  void nodesDidChange(const std::vector<Model::Node*>& nodes);
  void selectionDidChange(const Selection& selection);

private:
  void updateControls();
};

} // namespace View
} // namespace TrenchBroom
