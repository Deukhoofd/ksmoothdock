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

#include "desktop_selector.h"

#include <QApplication>
#include <QBrush>
#include <QColor>
#include <QDBusMessage>
#include <QDesktopWidget>
#include <QIcon>
#include <QPainter>
#include <QPixmap>

#include <KLocalizedString>
#include <KMessageBox>

#include "dock_panel.h"
#include <utils/font_utils.h>

namespace ksmoothdock {

DesktopSelector::DesktopSelector(DockPanel* parent, MultiDockModel* model,
                                 Qt::Orientation orientation, int minSize,
                                 int maxSize, int desktop)
    : IconBasedDockItem(parent, 
          i18n("Desktop ") + QString::number(desktop),
          orientation, "" /* no icon yet */, minSize, maxSize),
      model_(model),
      desktop_(desktop),
      plasmaShellDBus_("org.kde.plasmashell",
                       "/PlasmaShell",
                       "org.kde.PlasmaShell"),
      desktopWidth_(QApplication::desktop()->screenGeometry().width()),
      desktopHeight_(QApplication::desktop()->screenGeometry().height()) {}

void DesktopSelector::init() {
  loadConfig();
  createMenu();
  connect(KWindowSystem::self(), SIGNAL(currentDesktopChanged(int)),
          this, SLOT(updateWallpaper(int)));
  updateWallpaper(KWindowSystem::currentDesktop());
}

void DesktopSelector::draw(QPainter* painter) const {
  if (isWallpaperOk()) {
    IconBasedDockItem::draw(painter);
  } else {
    // Draw rectangles with desktop numbers if no custom wallpapers set.
    const auto bgColor = model_->backgroundColor();
    const QColor fillColor = bgColor.lighter();
    painter->fillRect(left_, top_, getWidth(), getHeight(), QBrush(fillColor));

    painter->setFont(adjustFontSize(getWidth(), getHeight(),
                                    "0",  // reference string
                                    0.5 /* scale factor */));
    painter->setRenderHint(QPainter::TextAntialiasing);
    painter->setPen(Qt::white);
    painter->drawText(left_, top_, getWidth(), getHeight(),Qt::AlignCenter,
                      QString::number(desktop_));
  }

  // Only draw the border for the current desktop if dock has border.
  if (isCurrentDesktop() && parent_->showBorder()) {
    painter->setPen(parent_->borderColor());
    painter->drawRect(left_ - 1, top_ - 1, getWidth() + 1, getHeight() + 1);
  }
}

void DesktopSelector::mousePressEvent(QMouseEvent* e) {
  if (e->button() == Qt::LeftButton) {
    if (isCurrentDesktop()) {
      KWindowSystem::setShowingDesktop(!KWindowSystem::showingDesktop());
    } else {
      KWindowSystem::setCurrentDesktop(desktop_);
    }
  } else if (e->button() == Qt::RightButton) {
    menu_.popup(e->globalPos());
  }
}

void DesktopSelector::loadConfig() {
  wallpaper_ = model_->wallpaper(desktop_);
  if (isWallpaperOk()) {
    setIconScaled(QPixmap(wallpaper_));
  } else {
    wallpaper_ = loadPlasmaWallpaper();
    if (isWallpaperOk()) {
      setIconScaled(QPixmap(wallpaper_));
    } else {
      setIconName("user-desktop");
    }
  }
}

void DesktopSelector::setIconScaled(const QPixmap& icon) {
  if (icon.width() * desktopHeight_ != icon.height() * desktopWidth_) {
    QPixmap scaledIcon = icon.scaled(desktopWidth_, desktopHeight_);
    setIcon(scaledIcon);
  } else {
    setIcon(icon);
  }
}

void DesktopSelector::updateWallpaper(int currentDesktop) {
  if (currentDesktop == desktop_) {
    setWallpaper(wallpaper_);
    parent_->update();
  }
}

void DesktopSelector::setWallpaper(const QString& wallpaper) {
  if (!plasmaShellDBus_.isValid()) {  // Not running in KDE Plasma 5.
    return;
  }

  if (wallpaper.isEmpty()) {
    return;
  }

  if (!QFile::exists(wallpaper)) {
    KMessageBox::error(
        nullptr,
        i18n("Failed to load wallpaper from: ") + wallpaper);
    return;
  }

  const QDBusMessage response = plasmaShellDBus_.call(
      "evaluateScript",
      "var allDesktops = desktops();"
      "for (i=0;i<allDesktops.length;i++) {"
      "d = allDesktops[i];"
      "d.wallpaperPlugin ='org.kde.image';"
      "d.currentConfigGroup = Array('Wallpaper', 'org.kde.image','General');"
      "d.writeConfig('Image','file://"
      + wallpaper + "')}");
  if (response.type() == QDBusMessage::ErrorMessage) {
    KMessageBox::error(
        nullptr,
        i18n("Failed to update wallpaper. Please make sure Plasma desktop "
             "widgets are unlocked in order to set wallpaper."));
  }
}

void DesktopSelector::createMenu() {
  menu_.addAction(
      QIcon::fromTheme("preferences-desktop-wallpaper"),
      i18n("Set Wallpaper for Desktop ") + QString::number(desktop_),
      parent_,
      [this] {
        parent_->showWallpaperSettingsDialog(desktop_);
      });
}

}  // namespace ksmoothdock
