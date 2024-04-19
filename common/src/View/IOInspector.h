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

#include "View/TabBook.h"

#include <memory>

class QSplitter;

namespace TrenchBroom::View
{

class IOOutputEditor;
class IOBrowser;
class GLContextManager;
class MapDocument;


class IOInspector : public TabBookPage
{
  Q_OBJECT
private:
  QSplitter* m_splitter = nullptr;
  IOOutputEditor* m_outputEditor = nullptr;

public:
  IOInspector(
    std::weak_ptr<MapDocument> document,
    GLContextManager& contextManager,
    QWidget* parent = nullptr);
  ~IOInspector() override;

private:
  void createGui(std::weak_ptr<MapDocument> document, GLContextManager& contextManager);
  // QWidget* createOutputEditor(QWidget* parent, std::weak_ptr<MapDocument> document);
  QWidget* createIOBrowser(QWidget* parent, std::weak_ptr<MapDocument> document);
};

} // namespace TrenchBroom::View
