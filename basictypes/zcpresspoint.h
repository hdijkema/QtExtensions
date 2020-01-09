#ifndef PRESSPOINT_H
#define PRESSPOINT_H
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

#include <QPointF>
#include <QJsonObject>
#include <QJsonValue>
#include <QDataStream>

#include "libqtextensions_global.h"

class LIBQTEXTENSIONS_EXPORT zcPressPoint : public QPointF {

private:
    qreal       _pressure;

public:
    zcPressPoint() {
        _pressure = 0.0;
    }

    zcPressPoint(qreal pressure,const QPointF & point) : QPointF(point) {
        _pressure = pressure;
    }

    zcPressPoint(qreal pressure, qreal x, qreal y) : QPointF(x, y) {
        _pressure = pressure;
    }

public:
    inline qreal      pressure() const       { return _pressure; }
    inline QPointF    point() const          { return *this; }
    inline void       setPressure(qreal p)   { _pressure = p; }

public:
    QJsonObject toJson() const;
    friend LIBQTEXTENSIONS_EXPORT QDataStream & operator << (QDataStream & out, const zcPressPoint & p);
    friend LIBQTEXTENSIONS_EXPORT QDataStream & operator << (QDataStream & out, const zcPressPoint * p);
    friend LIBQTEXTENSIONS_EXPORT QDataStream & operator >> (QDataStream & in, zcPressPoint & p);
    friend LIBQTEXTENSIONS_EXPORT QDataStream & operator >> (QDataStream & in, zcPressPoint * p);
    void fromJson(const QJsonObject &obj);
};


#endif // PRESSPOINT_H
