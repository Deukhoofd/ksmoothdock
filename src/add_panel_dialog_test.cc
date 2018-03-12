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

#include <memory>

#include <QPushButton>
#include <QTemporaryDir>
#include <QtTest>

namespace ksmoothdock {

constexpr int kDockId = 1;
constexpr int kScreen = 0;

class AddPanelDialogTest: public QObject {
  Q_OBJECT

 private slots:
  void init() {
    QTemporaryDir configDir;
    model_ = std::make_unique<MultiDockModel>(configDir.path());
    model_->addDock(PanelPosition::Bottom, kScreen);
    dialog_ = std::make_unique<AddPanelDialog>(model_.get(), kDockId);
  }

  // Tests OK button in Add mode.
  void add_ok();

  // Tests Cancel button in Add mode.
  void add_cancel();

  // Tests OK button in Clone mode.
  void clone_ok();

  // Tests Cancel button in Clone mode.
  void clone_cancel();

 private:
  std::unique_ptr<MultiDockModel> model_;
  std::unique_ptr<AddPanelDialog> dialog_;
};

void AddPanelDialogTest::add_ok() {
  QTest::mouseClick(dialog_->ui->buttonBox->button(QDialogButtonBox::Ok),
                    Qt::LeftButton);
  QCOMPARE(model_->dockCount(), 2);
}

void AddPanelDialogTest::add_cancel() {
  QTest::mouseClick(dialog_->ui->buttonBox->button(QDialogButtonBox::Cancel),
                    Qt::LeftButton);
  QCOMPARE(model_->dockCount(), 1);
}

void AddPanelDialogTest::clone_ok() {
  dialog_->setMode(AddPanelDialog::Mode::Clone);
  QTest::mouseClick(dialog_->ui->buttonBox->button(QDialogButtonBox::Ok),
                    Qt::LeftButton);
  QCOMPARE(model_->dockCount(), 2);
}

void AddPanelDialogTest::clone_cancel() {
  dialog_->setMode(AddPanelDialog::Mode::Clone);
  QTest::mouseClick(dialog_->ui->buttonBox->button(QDialogButtonBox::Cancel),
                    Qt::LeftButton);
  QCOMPARE(model_->dockCount(), 1);
}

}  // namespace ksmoothdock

QTEST_MAIN(ksmoothdock::AddPanelDialogTest)
#include "add_panel_dialog_test.moc"
