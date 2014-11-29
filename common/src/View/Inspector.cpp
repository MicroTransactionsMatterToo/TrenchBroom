/*
 Copyright (C) 2010-2014 Kristian Duske
 
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

#include "Inspector.h"

// #include "View/EntityInspector.h"
// #include "View/FaceInspector.h"
#include "View/MapInspector.h"
#include "View/TabBook.h"
#include "View/TabBar.h"

#include <wx/sizer.h>

namespace TrenchBroom {
    namespace View {
        Inspector::Inspector(wxWindow* parent, GLContextHolder::Ptr sharedContext, MapDocumentWPtr document) :
        wxPanel(parent),
        m_tabBook(NULL),
        m_mapInspector(NULL),
        m_entityInspector(NULL),
        m_faceInspector(NULL) {
            
            m_tabBook = new TabBook(this);

            m_mapInspector = new MapInspector(m_tabBook, sharedContext, document);
            // m_entityInspector = new EntityInspector(m_tabBook, sharedContext, document, controller);
            // m_faceInspector = new FaceInspector(m_tabBook, sharedContext, document, controller);
            
            m_tabBook->addPage(m_mapInspector, "Map");
            // m_tabBook->addPage(m_entityInspector, "Entity");
            // m_tabBook->addPage(m_faceInspector, "Face");
            
            wxSizer* sizer = new wxBoxSizer(wxVERTICAL);
            sizer->Add(m_tabBook, 1, wxEXPAND);
            SetSizer(sizer);
        }

        void Inspector::switchToPage(const InspectorPage page) {
            m_tabBook->switchToPage(static_cast<size_t>(page));
        }

        void Inspector::setTabBarHeight(const int height) {
            m_tabBook->setTabBarHeight(height);
        }
    }
}
