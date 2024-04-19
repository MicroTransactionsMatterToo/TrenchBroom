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

#ifndef IOINPUTLISTING_H
#define IOINPUTLISTING_H

namespace TrenchBroom::View
{
class MapDocument;
}
namespace TrenchBroom::View
{
class IOConnectionGrid;
}
namespace TrenchBroom {
namespace View {

class IOInputListing : public QWidget {
  Q_OBJECT
private:
  std::weak_ptr<MapDocument> m_document;
  IOConnectionGrid* m_inputGrid;

public:
  explicit IOInputListing(std::weak_ptr<MapDocument> document, QWidget* parent = nullptr);
  ~IOInputListing() override;

private:
  void createGui(std::weak_ptr<MapDocument> document);

};

} // View
} // TrenchBroom

#endif //IOINPUTLISTING_H
