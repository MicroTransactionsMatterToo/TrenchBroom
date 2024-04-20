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

#include "IOSlotModel.h"
#include "IOSlotTable.h"
#include "View/QtUtils.h"

namespace TrenchBroom
{
namespace View
{
IOSlotGrid::IOSlotGrid(const std::weak_ptr<MapDocument>& document, QWidget* parent)
  : QWidget{parent}
  , m_document{document}
{
  createGui(document);
}
void IOSlotGrid::createGui(std::weak_ptr<MapDocument> document)
{
  m_table = new IOSlotTable{};

  m_model = new IOSlotModel{document, this};

  m_table->setModel(m_model);

  autoResizeRows(m_table);

  m_table->verticalHeader()->setVisible(false);
  m_table->horizontalHeader()->setSectionResizeMode(
    IOSlotModel::ColumnSlotName, QHeaderView::ResizeToContents);
  m_table->horizontalHeader()->setSectionResizeMode(
    IOSlotModel::ColumnDescription, QHeaderView::Interactive);
  m_table->horizontalHeader()->setSectionResizeMode(
    IOSlotModel::ColumnParamType, QHeaderView::ResizeToContents);
  m_table->horizontalHeader()->setSectionResizeMode(
    IOSlotModel::ColumnDescription, QHeaderView::ResizeToContents);
  m_table->horizontalHeader()->setSectionsClickable(false);
  m_table->setSelectionBehavior(QAbstractItemView::SelectItems);

}
} // namespace View
} // namespace TrenchBroom