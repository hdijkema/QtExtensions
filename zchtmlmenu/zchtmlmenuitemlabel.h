#ifndef INTERNAL_ZCHTMLMENUITEMLABEL_H
#define INTERNAL_ZCHTMLMENUITEMLABEL_H
/**

    This file is part of QtExtensions (https://github.com/hdijkema/QtExtensions).

    (c) Hans Dijkema 2020

    QtExtensions is free software: you can redistribute it and/or modify
    it under the terms of the GNU Lesser General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    Qtextensions is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU Lesser General Public License
    along with QtExtensions. If not, see <https://www.gnu.org/licenses/lgpl.html>.

**/

#include <QWidget>
#include <QLabel>

class internal_zcHtmlMenuItemLabel : public QLabel
{
    Q_OBJECT
public:
    explicit internal_zcHtmlMenuItemLabel(QWidget *parent = nullptr);

    // QWidget interface
protected:
    void mouseReleaseEvent(QMouseEvent *event);
};

#endif // INTERNAL_ZCHTMLMENUITEMLABEL_H
