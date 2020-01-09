#ifndef LIBQTEXTENSIONS_H
#define LIBQTEXTENSIONS_H
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

#include "libqtextensions_global.h"

#include <QString>
#include <QList>

class LIBQTEXTENSIONS_EXPORT QtExtensions
{
public:
    QString version();
    QString license();
    QString licenseShort();
    QString author();
    QStringList classes();
};


#endif // LIBQTEXTENSIONS_H
