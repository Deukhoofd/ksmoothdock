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

#include "program.h"

#include <iostream>

#include <QProcess>

#include <KDesktopFile>
#include <KLocalizedString>
#include <KMessageBox>
#include <KWindowSystem>

#include <utils/draw_utils.h>

namespace ksmoothdock {

Program::Program(DockPanel* parent, MultiDockModel* model, const QString& label,
    Qt::Orientation orientation, const QString& iconName, int minSize,
    int maxSize, const QString& command)
    : IconBasedDockItem(parent, label, orientation, iconName, minSize, maxSize),
      model_(model),
      command_(command),
      launching_(false) {
  name_ = command_.left(command_.indexOf(" "));
}

Program::Program(DockPanel* parent, MultiDockModel* model, const QString& label,
    Qt::Orientation orientation, const QPixmap& icon, const QString& iconName, int minSize,
    int maxSize, const QString& command)
    : IconBasedDockItem(parent, label, orientation, icon, iconName, minSize, maxSize),
      model_(model),
      command_(command),
      launching_(false) {
  name_ = command_.left(command_.indexOf(" "));
}

void Program::draw(QPainter *painter) const {
  if (launching_ || (!tasks_.empty() && active())) {
    drawHighlightedIcon(model_->backgroundColor(), left_, top_, getWidth(), getHeight(),
                        5, size_ / 8, painter);
  } else if (!tasks_.empty()) {
    drawHighlightedIcon(model_->backgroundColor().darker(200), left_, top_, getWidth(), getHeight(),
                        5, size_ / 8, painter);
  }
  IconBasedDockItem::draw(painter);
}

void Program::mousePressEvent(QMouseEvent* e) {
  if (e->button() == Qt::LeftButton) { // Run the application.
    if (command_ == kShowDesktopCommand) {
      KWindowSystem::setShowingDesktop(!KWindowSystem::showingDesktop());
    } else {
      launch(command_);
    }
  }
}

bool Program::addTask(const TaskInfo& task) {
  if (name_ == task.program) {
    tasks_.push_back(ProgramTask(task.wId, task.name, task.demandsAttention));
    return true;
  }
  return false;
}

bool Program::beforeTask(const TaskInfo& task) {
  return name_ < task.program;
}

void Program::launch(const QString& command) {
  if (!QProcess::startDetached(command)) {
    KMessageBox::error(nullptr,
        i18n("Could not run command: ") + command);
  }
}

}  // namespace ksmoothdock
