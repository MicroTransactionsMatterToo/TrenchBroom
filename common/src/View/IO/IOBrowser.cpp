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

#include "IOBrowser.h"

#include "View/IO/IOSlotGrid.h"
#include "View/IO/IOSlotModel.h"
#include "View/MapDocument.h"
#include "View/QtUtils.h"
#include "View/Splitter.h"

#include "kdl/memory_utils.h"

namespace TrenchBroom
{
namespace View
{

IOBrowser::IOBrowser(const std::weak_ptr<MapDocument>& document, QWidget* parent)
  : QWidget{parent}
  , m_document{document}
{
  createGui(document);
}
void IOBrowser::createGui(const std::weak_ptr<MapDocument>& document)
{
  m_splitter = new Splitter{Qt::Horizontal};
  m_splitter->setObjectName("IOInspector_Browser_Splitter");

  createInputListing(m_splitter, document);
  createOutputListing(m_splitter, document);

  m_splitter->addWidget(m_inputListing);
  m_splitter->addWidget(m_outputListing);

  m_splitter->setSizes({100, 100});
  restoreWindowState(m_splitter);

  m_inputListing->setMinimumSize(100, 100);
  m_outputListing->setMinimumSize(100, 100);
  updateMinimumSize();

  m_splitter->setChildrenCollapsible(false);

  m_splitter->setStretchFactor(0, 1);
  m_splitter->setStretchFactor(1, 1);

  auto* layout = new QVBoxLayout{};
  layout->setContentsMargins(0, 0, 0, 0);
  layout->setSpacing(0);
  layout->addWidget(m_splitter, 1);
  setLayout(layout);
}

void IOBrowser::createOutputListing(
  QWidget* parent, const std::weak_ptr<MapDocument>& document)
{
  m_outputListing = new IOSlotGrid{document, parent};
  m_outputListing->setFilter(SlotDirection::Output);
}

void IOBrowser::createInputListing(
  QWidget* parent, const std::weak_ptr<MapDocument>& document)
{
  m_inputListing = new IOSlotGrid{document, parent};
  m_inputListing->setFilter(SlotDirection::Input);
}

void IOBrowser::connectObservers()
{
  auto document = kdl::mem_lock(m_document);
  m_notifierConnection +=
    document->selectionDidChangeNotifier.connect(this, &IOBrowser::selectionDidChange);
}
void IOBrowser::selectionDidChange(const Selection& selection)
{
  updateControls();
}
void IOBrowser::updateControls()
{
  updateMinimumSize();
}

void IOBrowser::updateMinimumSize()
{
  auto size = QSize{};
  size.setWidth(m_inputListing->minimumWidth() + m_outputListing->minimumWidth());
  size.setHeight(std::max(m_inputListing->minimumHeight(), m_outputListing->minimumHeight()));

  setMinimumSize(size);
  updateGeometry();
}
} // namespace View
} // namespace TrenchBroom