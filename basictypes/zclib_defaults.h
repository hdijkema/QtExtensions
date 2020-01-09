#ifndef ZCLIB_DEFAULTS_H
#define ZCLIB_DEFAULTS_H
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



#include <QObject>
#include <QDebug>
#include <QDataStream>

#define MAGIC_TYPE(t)               (static_cast<qint32>(t << 16))
#define MAGIC_VERSION(t, v)         (static_cast<qint32>(MAGIC_TYPE(t) + v))

#define MAGIC_GET_VERSION(magic)    (static_cast<int>(magic & 0xffff))
#define MAGIC_GET_TYPE(magic)       (static_cast<int>(magic >> 16))

#define MAGIC_IS_TYPE(m, t)         (MAGIC_GET_TYPE(m) == t)
#define MAGIC_IS_VERSION(m, v)      (MAGIC_GET_VERSION(m) == v)
#define MAGIC_LE_VERSION(m, v)      (MAGIC_GET_VERSION(m) > 0 && MAGIC_GET_VERSION(m) <= v)

inline int MAGIC_ASSERT2(qint32 magic, int t, int v) {
    if (!MAGIC_IS_TYPE(magic, t)) {
        QString msg = QObject::tr("Verkeerd bestandsformaat. Verwacht: %1, heb %2").arg(QString::number(t), QString::number(MAGIC_GET_TYPE(magic)));
        qCritical() << __FUNCTION__ << __LINE__ << msg;
        throw msg;
    }
    if (!MAGIC_LE_VERSION(magic, v)) {
        int file_version = MAGIC_GET_VERSION(magic);
        QString msg = QObject::tr("Niet ondersteunde versie van bestandsformaat %1, ondersteund: <=%2, verkregen: %3")
                .arg(QString::number(t), QString::number(v), QString::number(file_version));
        throw msg;
    }
    return MAGIC_GET_VERSION(magic);
}

inline int MAGIC_ASSERT(QDataStream & in, int t, int v) {
    qint32 magic;
    in >> magic;
    return MAGIC_ASSERT2(magic, t, v);
}

//////////////////////////////////////////////////////////////////
// Data Type Numbers
//////////////////////////////////////////////////////////////////

#define BEZIER_TYPE                 0x0A01
#define PRESSPOINT_TYPE             0x0A02
#define ZCCOLOR_TYPE                0x0A03
#define ZCFONT_TYPE                 0x0A04

#define BEZIER_MAGIC(v)             MAGIC_VERSION(BEZIER_TYPE, v)
#define PRESSPOINT_MAGIC(v)         MAGIC_VERSION(PRESSPOINT_TYPE, v)
#define ZCCOLOR_MAGIC(v)            MAGIC_VERSION(ZCCOLOR_TYPE, v)
#define ZCFONT_MAGIC(v)             MAGIC_VERSION(ZCFONT_TYPE, v)

#endif // ZCLIB_DEFAULTS_H
