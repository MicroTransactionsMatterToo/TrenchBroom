//
// Created by ennis on 11/04/24.
//

#include "IOInspector.h"

#include <QVBoxLayout>

#include "IOBrowser.h"
#include "View/BorderLine.h"
#include "View/CollapsibleTitledPanel.h"
#include "View/EntityBrowser.h"
#include "View/EntityDefinitionFileChooser.h"
#include "View/EntityPropertyEditor.h"
#include "View/MapDocument.h"
#include "View/QtUtils.h"
#include "View/Splitter.h"
#include "View/SwitchableTitledPanel.h"

namespace TrenchBroom::View
{
IOInspector::IOInspector(
  std::weak_ptr<MapDocument> document, GLContextManager& contextManager, QWidget* parent)
  : TabBookPage{parent}
{
  createGui(std::move(document), contextManager);
}
IOInspector::~IOInspector()
{
  saveWindowState(m_splitter);
}
void IOInspector::createGui(
  std::weak_ptr<MapDocument> document, GLContextManager& contextManager)
{
  m_splitter = new Splitter{Qt::Vertical};
  m_splitter->setObjectName("IOInspector_Splitter");

  // m_splitter->addWidget(createOutputEditor(m_splitter, document));
  m_splitter->addWidget(createIOBrowser(m_splitter, document));
}


QWidget* IOInspector::createIOBrowser(
  QWidget* parent, std::weak_ptr<MapDocument> document)
{
  return new IOBrowser{document, parent};
}

} // namespace TrenchBroom::View