/**

    This file is part of QtExtensions (https://github.com/hdijkema/QtExtensions).

    (c) Hans Dijkema 2020

    QtExtensions is free software: you can redistribute it and/or modify
    it under the terms of the GNU Lesser General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    Foobar is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU Lesser General Public License
    along with QtExtensions. If not, see <https://www.gnu.org/licenses/lgpl.html>.

**/

#include "zccoloricon.h"

#include <QPainter>

zcColorIcon::zcColorIcon()
    : zcColorIcon(zcColor(Qt::black))
{
}

zcColorIcon::zcColorIcon(const zcColor &color, bool square)
{
    int i, N, sz = 256;
    for(i = 0, N = 1 ; i < N; i++, sz *= 2) {
        QSize is(sz, sz);

        QPixmap icon(is);
        icon.fill(Qt::transparent);
        QPainter painter(&icon);
        painter.setRenderHint(QPainter::Antialiasing, true);
        painter.setRenderHint(QPainter::SmoothPixmapTransform, true);
        painter.setBrush(QBrush(color));
        painter.setPen(QPen(Qt::white));
        if (square) {
            QRect r(QPoint(0, 0), is);
            painter.drawRect(r);
        } else {
            QSize s(static_cast<int>(sz * 0.8), static_cast<int>(sz * 0.8));
            int ribbe = static_cast<int>(((sz * 0.2) / 2.0));
            QRect r(QPoint(ribbe,ribbe), s);
            painter.drawEllipse(r);
        }
        super::addPixmap(icon);
    }
}

zcColorIcon::zcColorIcon(char kind)
{
    int i, N, sz = 256;
    for(i = 0, N = 1 ; i < N; i++, sz *= 2) {
        int rsz = static_cast<int>(sz * 0.9);
        int csz = static_cast<int>(sz * 0.2);
        QSize s(rsz, rsz);
        QPixmap icon(s);
        icon.fill(Qt::transparent);
        QPainter painter(&icon);
        QBrush brush(Qt::gray);
        painter.setBrush(brush);
        painter.setPen(QPen(Qt::white));
        painter.fillRect(QRect(QPoint(0, rsz / 2 - (csz / 2)), QSize(rsz , csz)), brush);
        if (kind == '+') {
            painter.fillRect(QRect(QPoint(rsz / 2 - (csz / 2), 0), QSize(csz , rsz)), brush);
        }
        super::addPixmap(icon);
    }
}
