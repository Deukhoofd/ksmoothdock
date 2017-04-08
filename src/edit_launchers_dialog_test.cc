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

#include <memory>

#include <QTemporaryDir>
#include <QTemporaryFile>
#include <QtTest>

#include <KConfig>
#include <KConfigGroup>

#include "ksmoothdock.h"

namespace ksmoothdock {

class EditLaunchersDialogTest: public QObject {
  Q_OBJECT

 private slots:
  void init() {
    configFile_.reset(new QTemporaryFile);
    QVERIFY(configFile_->open());
    launchersDir_.reset(new QTemporaryDir);
    QVERIFY(launchersDir_->isValid());
    dock_.reset(new KSmoothDock(configFile_->fileName(),
                                launchersDir_->path()));
    dialog_ = dock_->editLaunchersDialog();
  }

  // Tests OK button/logic.
  void ok();

  // Tests Apply button/logic.
  void apply();

  // Tests Cancel button/logic.
  void cancel();

 private:
  EditLaunchersDialog* dialog_;
  std::unique_ptr<KSmoothDock> dock_;
  std::unique_ptr<QTemporaryFile> configFile_;
  std::unique_ptr<QTemporaryDir> launchersDir_;
};

void EditLaunchersDialogTest::ok() {
  QTest::mouseClick(dialog_->buttonBox_->button(QDialogButtonBox::Ok),
                    Qt::LeftButton);
}

void EditLaunchersDialogTest::apply() {
  QTest::mouseClick(dialog_->buttonBox_->button(QDialogButtonBox::Apply),
                    Qt::LeftButton);
}

void EditLaunchersDialogTest::cancel() {
  QTest::mouseClick(dialog_->buttonBox_->button(QDialogButtonBox::Cancel),
                    Qt::LeftButton);
}

}  // namespace ksmoothdock

QTEST_MAIN(ksmoothdock::EditLaunchersDialogTest)
#include "edit_launchers_dialog_test.moc"
