//
// Created by ennis on 12/04/24.
//

#pragma once
#include <QTableView>

namespace TrenchBroom {
namespace View {

class IOTable : public QTableView {
Q_OBJECT
public:
  explicit IOTable(QWidget* parent = nullptr);
};

} // View
} // TrenchBroom
