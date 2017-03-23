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

#include "edit_launchers_dialog.h"

#include <KLocalizedString>

#include "ksmoothdock.h"

namespace ksmoothdock {

EditLaunchersDialog::EditLaunchersDialog(KSmoothDock* parent)
    : QDialog(parent), parent_(parent) {
  setWindowTitle(i18n("Edit Launchers"));
  resize(1120, 610);

  launchers_ = new QListWidget(this);
  launchers_->setGeometry(QRect(20, 20, 441, 491));
  connect(
      launchers_,
      SIGNAL(currentItemChanged(QListWidgetItem*, QListWidgetItem*)),
      this,
      SLOT(refreshSelectedLauncher(QListWidgetItem*, QListWidgetItem*)));

  add_ = new QPushButton(this);
  add_->setText(i18n("Add"));
  add_->setGeometry(QRect(500, 50, 121, 38));
  remove_ = new QPushButton(this);
  remove_->setText(i18n("Remove"));
  remove_->setGeometry(QRect(500, 110, 121, 38));
  update_ = new QPushButton(this);
  update_->setText(i18n("Update"));
  update_->setGeometry(QRect(500, 170, 121, 38));

  openDir_ = new QPushButton(this);
  openDir_->setText(i18n("Open Folder"));
  openDir_->setGeometry(QRect(500, 300, 121, 38));
  connect(openDir_, SIGNAL(clicked()), parent_, SLOT(openLaunchersDir()));
  syncFromDir_ = new QPushButton(this);
  syncFromDir_->setText(i18n("Sync From\nFolder"));
  syncFromDir_->setGeometry(QRect(500, 360, 121, 61));

  nameLabel_ = new QLabel(this);
  nameLabel_->setText(i18n("Name"));
  nameLabel_->setGeometry(QRect(660, 30, 72, 22));
  name_ = new QLineEdit(this);
  name_->setGeometry(QRect(770, 20, 331, 36));

  commandLabel_ = new QLabel(this);
  commandLabel_->setText(i18n("Command"));
  commandLabel_->setGeometry(QRect(660, 110, 101, 22));
  command_ = new QLineEdit(this);
  command_->setGeometry(QRect(770, 100, 331, 36));
  browseExecutable_ = new QPushButton(this);
  browseExecutable_->setText(i18n("Browse Executable"));
  browseExecutable_->setGeometry(QRect(770, 160, 251, 38));

  internalCommands_ = new QComboBox(this);
  populateInternalCommands();
  internalCommands_->setGeometry(QRect(770, 220, 251, 36));
  connect(internalCommands_, SIGNAL(currentIndexChanged(int)),
      this, SLOT(updateInternalCommand(int)));

  dbusCommands_ = new QComboBox(this);
  populateDBusCommands();
  dbusCommands_->setGeometry(QRect(770, 280, 251, 36));
  connect(dbusCommands_, SIGNAL(currentIndexChanged(int)),
      this, SLOT(updateDBusCommand(int)));

  iconLabel_ = new QLabel(this);
  iconLabel_->setText(i18n("Icon"));
  iconLabel_->setGeometry(QRect(660, 450, 72, 22));
  icon_ = new KIconButton(this);
  icon_->setGeometry(QRect(770, 417, 101, 91));

  buttonBox_ = new QDialogButtonBox(this);
  buttonBox_->setGeometry(QRect(360, 550, 341, 32));
  buttonBox_->setOrientation(Qt::Horizontal);
  buttonBox_->setStandardButtons(QDialogButtonBox::Apply | QDialogButtonBox::Ok
      |QDialogButtonBox::Cancel);
  connect(buttonBox_, SIGNAL(accepted()), parent_, SLOT(updateConfig()));
  connect(buttonBox_, SIGNAL(rejected()), this, SLOT(reject()));
  connect(buttonBox_, SIGNAL(clicked(QAbstractButton*)), this,
      SLOT(buttonClicked(QAbstractButton*)));
}

void EditLaunchersDialog::buttonClicked(QAbstractButton* button) {
  auto role = buttonBox_->buttonRole(button);
  if (role == QDialogButtonBox::ApplyRole) {
    parent_->applyConfig();
  }
}

void EditLaunchersDialog::updateInternalCommand(int index) {
  if (index > 0) {  // Excludes header.
    command_->setText(internalCommands_->itemData(index).toString());
    dbusCommands_->setCurrentIndex(0);
  }
}

void EditLaunchersDialog::updateDBusCommand(int index) {
  if (index > 0) {  // Excludes header.
    command_->setText(dbusCommands_->itemData(index).toString());
    internalCommands_->setCurrentIndex(0);
  }
}

void EditLaunchersDialog::refreshSelectedLauncher(QListWidgetItem* current,
    QListWidgetItem* previous) {
  if (current != nullptr) {
    name_->setText(current->text());
    command_->setText(current->data(Qt::UserRole).toString());
    icon_->setIcon(current->icon());
  }
}

void EditLaunchersDialog::populateInternalCommands() {
  internalCommands_->addItem(i18n("Use an internal command"));  // header
  internalCommands_->addItem(i18n("Show desktop"), "SHOW_DESKTOP");
}

void EditLaunchersDialog::populateDBusCommands() {
  static const int kNumItems = 3;
  static const char* const kItems[kNumItems][2] = {
    // Description, D-Bus command.
    {"Lock the screen",
      "qdbus org.kde.screensaver /ScreenSaver Lock"},
    {"Suspend the computer",
      "qdbus org.kde.Solid.PowerManagement /org/freedesktop/PowerManagement "
      "Suspend"},
    {"Show the application menu",
      "qdbus org.kde.plasmashell /PlasmaShell activateLauncherMenu"}
  };
  dbusCommands_->addItem(i18n("Use a D-Bus command"));  // header
  for (int i = 0; i < kNumItems; ++i) {
    dbusCommands_->addItem(i18n(kItems[i][0]), kItems[i][1]);
  }
}

}  // namespace ksmoothdock
