#ifndef ZCDEBUG_H
#define ZCDEBUG_H

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

#include <QDebug>
#include <QTime>

#define LINE_DEBUG      qDebug() << __FUNCTION__ << __LINE__ << QTime::currentTime().toString("hh:mm:ss.zzz")
#define LINE_CRITICAL   qCritical() << __FUNCTION__ << __LINE__ << QTime::currentTime().toString("hh:mm:ss.zzz")
#define LINE_INFO       qInfo() << __FUNCTION__ << __LINE__ << QTime::currentTime().toString("hh:mm:ss.zzz")
#define LINE_WARNING    qWarning() << __FUNCTION__ << __LINE__ << QTime::currentTime().toString("hh:mm:ss.zzz")

#ifdef ZC_DEBUG
#define zcCRT dbg_mem_crt(typeid(*this).name(), reinterpret_cast<void *>(this));
#define zcDLT dbg_mem_dlt(typeid(*this).name(), reinterpret_cast<void *>(this));
#else
#define zcCRT
#define zcDLT
#endif

LIBQTEXTENSIONS_EXPORT void zc_dbg_mem_crt(const char *func, void *pointer);
LIBQTEXTENSIONS_EXPORT void zc_dbg_mem_dlt(const char *func, void *pointer);

#endif // ZCDEBUG_H
