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
#include "View/TabBook.h"


class QTextEdit;
namespace TrenchBroom
{
namespace View
{

class MapDocument;
class IOConnectionGrid;

class IOOutputEditor : public TabBookPage
{
  Q_OBJECT
private:
  std::weak_ptr<MapDocument> m_document;
  IOConnectionGrid* m_outputGrid;

  QTextEdit* m_documentationText;

public:
  explicit IOOutputEditor(std::weak_ptr<MapDocument> document, QWidget* parent = nullptr);
  ~IOOutputEditor() override;
};

} // namespace View
} // namespace TrenchBroom
