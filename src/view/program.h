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

#ifndef KSMOOTHDOCK_PROGRAM_H_
#define KSMOOTHDOCK_PROGRAM_H_

#include <vector>

#include "icon_based_dock_item.h"

#include <model/multi_dock_model.h>
#include <utils/command_utils.h>

namespace ksmoothdock {

struct ProgramTask {
  WId wId;
  QString name;  // e.g. home -- Dolphin
  bool demandsAttention;

  ProgramTask(WId wId2, QString name2, bool demandsAttention2)
    : wId(wId2), name(name2), demandsAttention(demandsAttention2) {}
};

class Program : public IconBasedDockItem {
 public:
  Program(DockPanel* parent, MultiDockModel* model, const QString& label,
      Qt::Orientation orientation, const QString& iconName, int minSize,
      int maxSize, const QString& command);

  ~Program() override = default;

  QString name() const { return name_; }

  QString command() const { return command_; }

  void setLaunching(bool launching) { launching_ = launching; }

  void draw(QPainter* painter) const override;

  void mousePressEvent(QMouseEvent* e) override;

  void addTask(const ProgramTask& task) {
    tasks_.push_back(task);
  }

  static void launch(const QString& command);
  static void lockScreen() { launch(kLockScreenCommand); }

 private:
  MultiDockModel* model_;
  QString name_;
  QString command_;
  bool launching_;
  std::vector<ProgramTask> tasks_;

  friend class DockPanel;
};

}  // namespace ksmoothdock

#endif  // KSMOOTHDOCK_PROGRAM_H_
