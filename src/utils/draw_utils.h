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

#ifndef KSMOOTHDOCK_DRAW_UTILS_H_
#define KSMOOTHDOCK_DRAW_UTILS_H_

#include <QColor>
#include <QPainter>
#include <QString>

namespace ksmoothdock {

inline void drawBorderedText(int x, int y, const QString& text, int borderWidth,
                             QColor borderColor, QColor textColor,
                             QPainter* painter) {
  painter->setPen(borderColor);
  for (int i = -borderWidth; i <= borderWidth; ++i) {
    for (int j = -borderWidth; j <= borderWidth; ++j) {
      painter->drawText(x + i, y + j, text);
    }
  }

  painter->setPen(textColor);
  painter->drawText(x, y, text);
}

inline void drawBorderedText(int x, int y, int width, int height, int flags,
                             const QString& text, int borderWidth,
                             QColor borderColor, QColor textColor,
                             QPainter* painter) {
  painter->setPen(borderColor);
  for (int i = -borderWidth; i <= borderWidth; ++i) {
    for (int j = -borderWidth; j <= borderWidth; ++j) {
      painter->drawText(x + i, y + j, width, height, flags, text);
    }
  }

  painter->setPen(textColor);
  painter->drawText(x, y, width, height, flags, text);
}

}  // namespace ksmoothdock

#endif  // KSMOOTHDOCK_DRAW_UTILS_H_
