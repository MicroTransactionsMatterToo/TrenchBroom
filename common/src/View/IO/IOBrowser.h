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


class QSplitter;
namespace TrenchBroom
{
namespace View
{
class MapDocument;
class IOSlotGrid;

class IOBrowser : public QWidget
{
  Q_OBJECT
private:
  QSplitter* m_splitter = nullptr;
  IOSlotGrid* m_outputListing = nullptr;
  IOSlotGrid* m_inputListing = nullptr;

public:
  explicit IOBrowser(std::weak_ptr<MapDocument> document, QWidget* parent = nullptr);

private:
  void createGui(std::weak_ptr<MapDocument> document);
  QWidget* createOutputListing(QWidget* parent, std::weak_ptr<MapDocument> document);
  QWidget* createInputListing(QWidget* parent, std::weak_ptr<MapDocument> document);
};

} // namespace View
} // namespace TrenchBroom
