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

#include "IOConnectionEditor.h"

#include "IOInputListing.h"
#include "IOOutputEditor.h"
#include "View/QtUtils.h"
#include "View/TabBook.h"

namespace TrenchBroom
{
namespace View
{
IOConnectionEditor::IOConnectionEditor(
  const std::weak_ptr<MapDocument>& document, QWidget* parent)
  : QWidget{parent}
  , m_document{document}
{
  createGui();
}
IOConnectionEditor::~IOConnectionEditor() = default;

void IOConnectionEditor::createGui()
{
  m_tabBook = new TabBook{};

  createOutputEditor();
  createInputListing();

  m_tabBook->addPage(m_outputEditor, "Outputs");
  m_tabBook->addPage(m_inputListing, "Inputs");

  auto* layout = new QVBoxLayout{};
  layout->setContentsMargins(0, 0, 0, 0);
  layout->addWidget(m_tabBook);
  setLayout(layout);
}
void IOConnectionEditor::createOutputEditor()
{
  m_outputEditor = new IOOutputEditor{m_document, m_tabBook};
}
void IOConnectionEditor::createInputListing()
{
  m_inputListing = new IOInputListing{m_document, m_tabBook};
}

} // namespace View
} // namespace TrenchBroom