#include "libqtextensions.h"
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

/*!
 * \page Qt Extensions
 *
 * QtExtensions provides a library with extensions to the Qt Widgetset.
 * The following classes are provided:
 *
 * \list
 * \li libqtextensions - provided classes:
 *   \list
 *   \li zcHtmlMenu
 *   \li zcHtmlDelegate
 *   \endlist
 * \endlist
 */

#include <QObject>

QString QtExtensions::version()
{
    QString ver(QObject::tr("QtExtensions version %1.%2").arg(
                    QString::number(QTEXTENSIONS_VERSION_MAJOR),
                    QString::number(QTEXTENSIONS_VERSION_MINOR)
                    )
                );
    return ver;
}

QString QtExtensions::license()
{
    return QString(QObject::tr("GNU Lesser General Public License version 3"));
}

QString QtExtensions::licenseShort()
{
    return QString("LGPLv3");
}

QString QtExtensions::author()
{
    return QString("(c) %1 Hans Dijkema").arg(QTEXTENSIONS_DEVEL_YEARS);
}
