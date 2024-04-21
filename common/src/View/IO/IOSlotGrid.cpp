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

#include "IOSlotGrid.h"

#include <QHeaderView>
#include <QTimer>

#include "IOSlotModel.h"
#include "IOSlotTable.h"
#include "View/MapDocument.h"
#include "View/QtUtils.h"

#include "kdl/memory_utils.h"

namespace TrenchBroom
{
namespace View
{
IOSlotGrid::IOSlotGrid(const std::weak_ptr<MapDocument>& document, QWidget* parent)
  : QWidget{parent}
  , m_document{document}
{
  createGui(document);
  connectObservers();
}
void IOSlotGrid::createGui(const std::weak_ptr<MapDocument>& document)
{
  m_table = new IOSlotTable{};

  m_model = new IOSlotModel{document, this};

  m_table->setModel(m_model);

  autoResizeRows(m_table);

  m_table->verticalHeader()->setVisible(false);
  m_table->horizontalHeader()->setVisible(true);
  m_table->horizontalHeader()->setSectionResizeMode(
    IOSlotModel::ColumnDirection, QHeaderView::Fixed);
  m_table->horizontalHeader()->resizeSection(IOSlotModel::ColumnDirection, 50);
  m_table->horizontalHeader()->setSectionResizeMode(
    IOSlotModel::ColumnSlotName, QHeaderView::ResizeToContents);
  m_table->horizontalHeader()->setSectionResizeMode(
    IOSlotModel::ColumnParamType, QHeaderView::ResizeToContents);
  m_table->horizontalHeader()->setStretchLastSection(true);
  m_table->horizontalHeader()->setSectionsClickable(false);
  m_table->setSelectionBehavior(QAbstractItemView::SelectItems);


  auto* layout = new QVBoxLayout{};
  layout->setContentsMargins(0, 0, 0, 0);
  layout->setSpacing(0);
  layout->addWidget(m_table, 1);
  setLayout(layout);
}
void IOSlotGrid::setFilter(const SlotDirection filter) const
{
  m_model->setFilter(filter);
}

void IOSlotGrid::connectObservers()
{
  auto document = kdl::mem_lock(m_document);
  m_notifierConnection +=
    document->documentWasNewedNotifier.connect(this, &IOSlotGrid::documentWasNewed);
  m_notifierConnection +=
    document->documentWasLoadedNotifier.connect(this, &IOSlotGrid::documentWasLoaded);
  m_notifierConnection +=
    document->selectionDidChangeNotifier.connect(this, &IOSlotGrid::selectionDidChange);
}
void IOSlotGrid::documentWasNewed(MapDocument* document)
{
  updateControls();
}
void IOSlotGrid::documentWasLoaded(MapDocument* document)
{
  updateControls();
}
void IOSlotGrid::nodesDidChange(const std::vector<Model::Node*>& nodes)
{
  qDebug() << "NodesDidChange";
  updateControls();
}
void IOSlotGrid::selectionDidChange(const Selection& selection)
{
  qDebug() << "SelectionDidChange ENTER";
  updateControls();
  qDebug() << "SelectionDidChange EXIT";
}
void IOSlotGrid::updateControls()
{
  QTimer::singleShot(0, this, [&]() { m_model->updateFromMapDocument(); });
}
} // namespace View
} // namespace TrenchBroom