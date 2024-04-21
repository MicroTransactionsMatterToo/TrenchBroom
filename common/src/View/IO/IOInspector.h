//
// Created by ennis on 19/04/24.
//

#pragma once

#include "View/TabBook.h"

#include <memory>

namespace TrenchBroom::View
{
class MapDocument;
}
namespace TrenchBroom::View
{
class IOBrowser;
}
namespace TrenchBroom::View
{
class IOConnectionEditor;
}
class QSplitter;

namespace TrenchBroom
{
namespace View
{

class IOInspector : public TabBookPage
{
  Q_OBJECT
private:
  QSplitter* m_splitter = nullptr;
  QWidget* m_connectionEditor = nullptr;
  IOBrowser* m_ioBrowser = nullptr;

public:
  IOInspector(std::weak_ptr<MapDocument> document, QWidget* parent = nullptr);
  ~IOInspector() override;

private:
  void createGui(std::weak_ptr<MapDocument> document);
  void createConnectionEditor(QWidget* parent, std::weak_ptr<MapDocument> document);
  void createIOBrowser(QWidget* parent, const std::weak_ptr<MapDocument>& document);
};

} // namespace View
} // namespace TrenchBroom
