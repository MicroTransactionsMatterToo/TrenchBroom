//
// Created by ennis on 19/04/24.
//

#include "IOInspector.h"

#include "View/IO/IOBrowser.h"
#include "View/IO/IOConnectionEditor.h"
#include "View/QtUtils.h"
#include "View/Splitter.h"

namespace TrenchBroom
{
namespace View
{

IOInspector::IOInspector(std::weak_ptr<MapDocument> document, QWidget* parent)
  : TabBookPage{parent}
{
  createGui(document);
}
IOInspector::~IOInspector()
{
  saveWindowState(m_splitter);
}
void IOInspector::createGui(std::weak_ptr<MapDocument> document)
{
  m_splitter = new Splitter{Qt::Vertical};
  m_splitter->setObjectName("IOInspector_Splitter");

  createIOBrowser(m_splitter, document);

  // m_splitter->addWidget(m_connectionEditor);
  m_splitter->addWidget(m_ioBrowser);

  m_splitter->setStretchFactor(0, 1);
  // m_splitter->setStretchFactor(1, 1);

  // m_connectionEditor->setMinimumSize(100, 150);
  m_ioBrowser->setMinimumSize(100, 150);

  auto* layout = new QVBoxLayout{};
  layout->setContentsMargins(0, 0, 0, 0);
  layout->addWidget(m_splitter, 1);
  setLayout(layout);

  restoreWindowState(m_splitter);
}

void IOInspector::createConnectionEditor(
  QWidget* parent, std::weak_ptr<MapDocument> document)
{
  m_connectionEditor = new QWidget{parent};
}
void IOInspector::createIOBrowser(
  QWidget* parent, const std::weak_ptr<MapDocument>& document)
{
  m_ioBrowser = new IOBrowser{document, parent};
}
} // namespace View
} // namespace TrenchBroom