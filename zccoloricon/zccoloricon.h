#ifndef ZCCANVASICON_H
#define ZCCANVASICON_H
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

#include <QIcon>
#include "zccolor.h"

#ifdef Q_QDOC
class zcColorIcon : public QIcon
#else
class LIBQTEXTENSIONS_EXPORT zcColorIcon : public QIcon
#endif
{
private:
    typedef QIcon super;

public:
    zcColorIcon();
    zcColorIcon(const zcColor & color, bool square = false);
    zcColorIcon(const QColor & color, bool square = false);
    zcColorIcon(char kind);
};

#endif // ZCCANVASICON_H
