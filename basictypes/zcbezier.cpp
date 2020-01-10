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
#include "zcbezier.h"
#include <QtMath>
#include "zclib_defaults.h"

LIBQTEXTENSIONS_EXPORT QDebug & operator<<(QDebug & d, const zcBezier & input)
{
    d << "start:" << input._start << "," << input._startPressure
      << ", c1:" << input._control1 << ", c2:" << input._control2
      << ", end:" << input._end << "," << input._endPressure;
    return d;
}

static inline qreal point(qreal t, qreal start, qreal c1, qreal c2, qreal end) {
    return          start * (1.0 - t) * (1.0 - t)  * (1.0 - t)
           + 3.0 *  c1    * (1.0 - t) * (1.0 - t)  * t
           + 3.0 *  c2    * (1.0 - t) * t          * t
           +        end   * t         * t          * t;
}

void zcBezier::addDy(qreal dyPt)
{
    _start.setY(_start.y() + dyPt);
    _end.setY(_end.y() + dyPt);
    _control1.setY(_control1.y() + dyPt);
    _control2.setY(_control2.y() + dyPt);
}

qreal zcBezier::length() {
    int steps = 10;
    qreal length = 0.0;
    int i;
    qreal t, cx, cy, px = 0, py = 0, xdiff, ydiff;

    for(i = 0; i <= steps; i++) {
        t = (static_cast<qreal>(i) / steps);
        cx = point(t, _start.x(), _control1.x(), _control2.x(), _end.x());
        cy = point(t, _start.y(), _control1.y(), _control2.y(), _end.y());
        if (i > 0) {
            xdiff = cx - px;
            ydiff = cy - py;
            length += qSqrt(xdiff * xdiff + ydiff * ydiff);
        }
        px = cx;
        py = cy;
    }
    return length;
}

QJsonObject zcBezier::toJson() const
{
    QJsonObject obj;
#define P(a, o)     obj[a/**/"x"] = o.x(); obj[a/**/"y"] = o.y()
    P("s", _start);
    P("e", _end);
    P("c1", _control1);
    P("c2", _control2);
#undef P
    obj["ps"] = _startPressure;
    obj["pe"] = _endPressure;
    return obj;
}

QDataStream & operator << (QDataStream & out, const zcBezier & b) {
    out << BEZIER_MAGIC(1);
#define P(v)    out << v.x(); out << v.y()
    P(b._start);
    P(b._end);
    P(b._control1);
    P(b._control2);
#undef P
    out << b._startPressure;
    out << b._endPressure;
    return out;
}

QDataStream & operator << (QDataStream & out, const zcBezier * b) {
    return operator <<(out, *b);
}


void zcBezier::fromJson(const QJsonObject &obj) {
#define P(a)    QPointF(obj[a/**/"x"].toDouble(), obj[a/**/"y"].toDouble())
    _start = P("s");
    _end = P("e");
    _control1 = P("c1");
    _control2 = P("c2");
#undef P
    _startPressure = obj["ps"].toDouble();
    _endPressure = obj["pe"].toDouble();
}

LIBQTEXTENSIONS_EXPORT QDataStream & operator >> (QDataStream & in, zcBezier & b) {
    MAGIC_ASSERT(in, BEZIER_TYPE, 1);
#define P(p)    { qreal x, y; in >> x; in >> y; p.setX(x);p.setY(y); }
    P(b._start)
    P(b._end)
    P(b._control1)
    P(b._control2)
#undef P
    in >> b._startPressure;
    in >> b._endPressure;
    return in;
}

LIBQTEXTENSIONS_EXPORT QDataStream & operator >> (QDataStream & in, zcBezier * b) {
    return operator >>(in, *b);
}
