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

#include "multi_dock_model.h"

#include <QFile>
#include <QTemporaryDir>
#include <QtTest>

namespace ksmoothdock {

class MultiDockModelTest: public QObject {
  Q_OBJECT

 private slots:
  void load_noDock();

  void load_singleDock();

  void load_multipleDocks();

 private:
  void createDockConfig(const QTemporaryDir& configDir, int fileId) {
    QFile dockConfig(configDir.path() + "/" +
                     ConfigHelper::dockConfigFile(fileId));
    dockConfig.open(QIODevice::WriteOnly);
  }
};

void MultiDockModelTest::load_noDock() {
  QTemporaryDir configDir;
  MultiDockModel model(configDir.path());
  QCOMPARE(model.dockCount(), 0);
}

void MultiDockModelTest::load_singleDock() {
  QTemporaryDir configDir;
  QVERIFY(configDir.isValid());
  createDockConfig(configDir, 1);

  MultiDockModel model(configDir.path());
  QCOMPARE(model.dockCount(), 1);
}

void MultiDockModelTest::load_multipleDocks() {
  QTemporaryDir configDir;
  QVERIFY(configDir.isValid());
  createDockConfig(configDir, 1);
  createDockConfig(configDir, 2);
  createDockConfig(configDir, 4);

  MultiDockModel model(configDir.path());
  QCOMPARE(model.dockCount(), 3);
}

}  // namespace ksmoothdock

QTEST_MAIN(ksmoothdock::MultiDockModelTest)
#include "multi_dock_model_test.moc"
