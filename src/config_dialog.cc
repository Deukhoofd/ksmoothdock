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

#include "config_dialog.h"

#include <KLocalizedString>

#include "ksmoothdock.h"

namespace ksmoothdock {

ConfigDialog::ConfigDialog(KSmoothDock* parent)
    : QDialog(parent), parent_(parent) {
  setWindowTitle(i18n("Panel Settings"));
  resize(680, 280);

  minSizeLabel_ = new QLabel(this);
  minSizeLabel_->setText(i18n("Minimum icon size"));
  minSizeLabel_->setGeometry(QRect(40, 30, 161, 22));
  minSize_ = new QSpinBox(this);
  minSize_->setGeometry(QRect(210, 20, 61, 36));
  minSize_->setMinimum(16);
  minSize_->setMaximum(64);
  minSize_->setSingleStep(8);

  maxSizeLabel_ = new QLabel(this);
  maxSizeLabel_->setText(i18n("Maximum icon size"));
  maxSizeLabel_->setGeometry(QRect(380, 30, 161, 22));
  maxSize_ = new QSpinBox(this);
  maxSize_->setGeometry(QRect(550, 20, 71, 36));
  maxSize_->setMinimum(32);
  maxSize_->setMaximum(192);
  maxSize_->setSingleStep(8);

  backgroundColorLabel_ = new QLabel(this);
  backgroundColorLabel_->setText(i18n("Background color"));
  backgroundColorLabel_->setGeometry(QRect(40, 90, 151, 22));
  backgroundColor_ = new KColorButton(this);
  backgroundColor_->setAlphaChannelEnabled(false);
  backgroundColor_->setGeometry(QRect(210, 80, 81, 38));

  borderColorLabel_ = new QLabel(this);
  borderColorLabel_->setText(i18n("Border color"));
  borderColorLabel_->setGeometry(QRect(380, 90, 141, 22));
  borderColor_ = new KColorButton(this);
  borderColor_->setAlphaChannelEnabled(false);
  borderColor_->setGeometry(QRect(550, 80, 71, 38));

  tooltipFontSizeLabel_ = new QLabel(this);
  tooltipFontSizeLabel_->setText(i18n("Tooltip font size"));
  tooltipFontSizeLabel_->setGeometry(QRect(40, 160, 141, 22));
  tooltipFontSize_ = new QSpinBox(this);
  tooltipFontSize_->setGeometry(QRect(210, 150, 56, 36));
  tooltipFontSize_->setMinimum(8);
  tooltipFontSize_->setMaximum(28);
  tooltipFontSize_->setSingleStep(2);

  buttonBox_ = new QDialogButtonBox(this);
  buttonBox_->setGeometry(QRect(170, 220, 341, 32));
  buttonBox_->setOrientation(Qt::Horizontal);
  buttonBox_->setStandardButtons(QDialogButtonBox::Ok
      | QDialogButtonBox::Apply | QDialogButtonBox::RestoreDefaults
      | QDialogButtonBox::Cancel);

  connect(buttonBox_, SIGNAL(accepted()), parent_, SLOT(updateConfig()));
  connect(buttonBox_, SIGNAL(rejected()), this, SLOT(reject()));
  connect(buttonBox_, SIGNAL(clicked(QAbstractButton*)), this,
      SLOT(buttonClicked(QAbstractButton*)));
}

void ConfigDialog::buttonClicked(QAbstractButton* button) {
  auto role = buttonBox_->buttonRole(button);
  if (role == QDialogButtonBox::ApplyRole) {
    parent_->applyConfig();
  } else if (role == QDialogButtonBox::ResetRole) {
    parent_->resetConfig();
  }
}

}  // namespace ksmoothdock
