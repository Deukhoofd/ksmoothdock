/*
 * This file is part of KSmoothDock.
 * Copyright (C) 2017 Viet Dang (dangvd@gmail.com)
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

#ifndef KSMOOTHDOCK_ICON_BASED_DOCK_ITEM_H_
#define KSMOOTHDOCK_ICON_BASED_DOCK_ITEM_H_

#include <qicon.h>
#include <qimage.h>
#include <vector>

#include <QPainter>
#include <QPixmap>
#include <QString>
#include <Qt>

#include "dock_item.h"

namespace ksmoothdock {

// Base class for icon-based dock items, such as launchers and pager icons.
class IconBasedDockItem : public DockItem {
 public:
  IconBasedDockItem(DockPanel* parent, const QString& label, Qt::Orientation orientation,
                    const QString& iconName, int minSize, int maxSize);
  IconBasedDockItem(DockPanel* parent, const QString& label, Qt::Orientation orientation,
                    const QPixmap& icon, int minSize, int maxSize);
  virtual ~IconBasedDockItem() {}

  int getWidthForSize(int size) const override {
    return size_;
  }

  int getHeightForSize(int size) const override {
      return size_;
  }

  void draw(QPainter* painter) const override;

  // Sets the icon on the fly.
  void setIcon(const QPixmap& icon);
  void setIconName(const QString& iconName);
  const QIcon& getIcon(int size) const;
  QString getIconName() const { return iconName_; }

 protected:
  QIcon icon;

  QString iconName_;
  QImage originalImage;

 private:
  static const int kIconLoadSize = 128;

  void generateIcons(const QPixmap& icon);

  friend class DockPanel;
};

}  // namespace ksmoothdock

#endif  // KSMOOTHDOCK_ICON_BASED_DOCK_ITEM_H_
