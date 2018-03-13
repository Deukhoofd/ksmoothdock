/*
 * This file is part of KSmoothDock.
 * Copyright (C) 2018 Viet Dang (dangvd@gmail.com)
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

#include "add_panel_dialog.h"
#include "ui_add_panel_dialog.h"

#include <QApplication>
#include <QDesktopWidget>

#include <KLocalizedString>

namespace ksmoothdock {

AddPanelDialog::AddPanelDialog(Mode mode, MultiDockModel* model, int dockId)
    : QDialog(nullptr),
      ui(new Ui::AddPanelDialog),
      mode_(mode),
      model_(model),
      dockId_(dockId) {
  ui->setupUi(this);

  // Populate screen list.

  const int screenCount = QApplication::desktop()->screenCount();
  for (int i = 1; i <= screenCount; ++i) {
    ui->screen->addItem(QString::number(i));
  }
  ui->screen->setCurrentIndex(0);

  // Adjust the UI for single/multi-screen.

  const bool isSingleScreen = (screenCount == 1);
  if (isSingleScreen) {
    ui->screenLabel->setVisible(false);
    ui->screen->setVisible(false);

    constexpr int kDeltaY = 45;
    ui->buttonBox->move(ui->buttonBox->x(), ui->buttonBox->y() - kDeltaY);
    resize(width(), height() - kDeltaY);
  }

  // Adjust the UI for different modes.

  setWindowTitle((mode_ == Mode::Add)
                 ? i18n("Add Panel") : (mode_ == Mode::Clone)
                    ? i18n("Clone Panel") : i18n("Welcome to KSmoothDock!"));

  if (mode == Mode::Welcome) {
    ui->headerLabel->setText(i18n("Please set up your first panel."));
  }

  if (mode == Mode::Add) {
    ui->showApplicationMenu->setChecked(false);
    ui->showPager->setChecked(false);
    ui->showClock->setChecked(false);
  } else if (mode == Mode::Clone) {
    ui->componentsLabel->setVisible(false);
    ui->showApplicationMenu->setVisible(false);
    ui->showLaunchers->setVisible(false);
    ui->showPager->setVisible(false);
    ui->showClock->setVisible(false);

    constexpr int kDeltaY = 200;
    ui->positionLabel->move(ui->positionLabel->x(),
                            ui->positionLabel->y() - kDeltaY);
    ui->position->move(ui->position->x(), ui->position->y() - kDeltaY);
    ui->screenLabel->move(ui->screenLabel->x(), ui->screenLabel->y() - kDeltaY);
    ui->screen->move(ui->screen->x(), ui->screen->y() - kDeltaY);
    ui->buttonBox->move(ui->buttonBox->x(), ui->buttonBox->y() - kDeltaY);
    resize(width(), height() - kDeltaY);
  }
}

AddPanelDialog::~AddPanelDialog() {
  delete ui;
}

void AddPanelDialog::accept() {
  QDialog::accept();
  auto position = static_cast<PanelPosition>(ui->position->currentIndex());
  auto screen = ui->screen->currentIndex();
  if (mode_ == Mode::Clone) {
    model_->cloneDock(dockId_, position, screen);
  } else {
    model_->addDock(position, screen);
  }
}

}  // namespace ksmoothdock
