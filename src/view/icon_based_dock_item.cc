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

#include "icon_based_dock_item.h"

#include <KIconLoader>

#include <QImage>
#include <qicon.h>

namespace ksmoothdock {

const int IconBasedDockItem::kIconLoadSize;

IconBasedDockItem::IconBasedDockItem(DockPanel* parent, const QString& label, Qt::Orientation orientation,
                  const QString& iconName, int minSize, int maxSize)
    : DockItem(parent, label, orientation, minSize, maxSize){
  setIconName(iconName);
}

IconBasedDockItem::IconBasedDockItem(DockPanel* parent, const QString& label,
    Qt::Orientation orientation, const QPixmap& icon,
    int minSize, int maxSize)
    : DockItem(parent, label, orientation, minSize, maxSize) {
  setIcon(icon);
}

void IconBasedDockItem::draw(QPainter* painter) const {
    icon.paint(painter, left_, top_, size_, size_);
}

void IconBasedDockItem::setIcon(const QPixmap& pixmap) {
  generateIcons(pixmap);
}

void IconBasedDockItem::setIconName(const QString& iconName) {
  if (!iconName.isEmpty()) {
    iconName_ = iconName;
    QPixmap pixmap = KIconLoader::global()->loadIcon(iconName,
        KIconLoader::NoGroup, kIconLoadSize);
    setIcon(pixmap);
  }
}

const QIcon& IconBasedDockItem::getIcon(int size) const {
  return icon;
}

void IconBasedDockItem::generateIcons(const QPixmap& pixmap) {
    icon = QIcon(pixmap);
}

}  // namespace ksmoothdock
