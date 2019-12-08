/*
 * This file is part of KSmoothDock.
 * Copyright (C) 2019 Viet Dang (dangvd@gmail.com)
 *
 * KSmoothDock is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * KSmoothDock is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with KSmoothDock.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef KSMOOTHDOCK_SEPARATOR_H_
#define KSMOOTHDOCK_SEPARATOR_H_

#include "iconless_dock_item.h"

#include <QAction>
#include <QMenu>
#include <QObject>
#include <QString>

#include "calendar.h"
#include <model/multi_dock_model.h>

namespace ksmoothdock {

// A digital Separator.
class Separator : public QObject, public IconlessDockItem {
  Q_OBJECT

 public:
  Separator(DockPanel* parent, MultiDockModel* model, Qt::Orientation orientation,
        int minSize, int maxSize);
  virtual ~Separator() = default;

  void draw(QPainter* painter) const override;
  void mousePressEvent(QMouseEvent* e) override;
  bool beforeTask(const QString& command) override { return false; }

 private:
  static constexpr float kWhRatio = 0.1;

  // Creates the context menu.
  void createMenu();

  MultiDockModel* model_;

  // Context menu.
  QMenu menu_;

  QAction* removeAction_;
};

}  // namespace ksmoothdock

#endif  // KSMOOTHDOCK_SEPARATOR_H_
