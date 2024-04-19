//
// Created by ennis on 11/04/24.
//

#include "IOBrowser.h"

#include <QSortFilterProxyModel>

#include "IOItemDelegate.h"
#include "IOPropertyModel.h"
#include "IOTable.h"

namespace TrenchBroom
{
namespace View
{

class IOSortFilterProxyModel;

IOBrowser::IOBrowser(std::weak_ptr<MapDocument> document, QWidget* parent)
  : QWidget{parent}
  , m_document{std::move(document)}
{
  createGui(m_document);
}

class IOSortFilterProxyModel : public QSortFilterProxyModel
{
public:
  explicit IOSortFilterProxyModel(QObject* parent = nullptr)
    : QSortFilterProxyModel{parent}
  {
  }
};

void IOBrowser::createGui(std::weak_ptr<MapDocument> document)
{
  m_table = new IOTable{};
  m_model = new IOPropertyModel{document, this};

  m_proxyModel = new IOSortFilterProxyModel{this};
  m_proxyModel->setSourceModel(m_model);

  m_table->setModel(m_proxyModel);
  m_table->setItemDelegate(new IOItemDelegate{m_table, m_model, m_proxyModel, m_table});
}


} // namespace View
} // namespace TrenchBroom