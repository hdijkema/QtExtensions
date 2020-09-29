#ifndef ZCCOLOR_H
#define ZCCOLOR_H
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

#include <QColor>
#include <QJsonObject>
#include <QDataStream>

#include "libqtextensions_global.h"

#ifdef Q_QDOC
class zcColor : public QColor
#else
class LIBQTEXTENSIONS_EXPORT zcColor : public QColor
#endif
{
private:
    typedef QColor super;
    bool _invalid;

public:
    explicit zcColor(QColor col);
    explicit zcColor(int color = Qt::black);
    explicit zcColor(int r, int g, int b, int a = 255);
    explicit zcColor(const char *htmlColor);
    explicit zcColor(QString htmlColor);

public:
    static zcColor fromHTML(const QString & htmlColor);
    static zcColor invalidColor();
    QString toHTML() const;

    qint32 toIntRgb() const;

public:
    bool equals(QColor other);
    bool isTransparent();
    void interpolateTo(zcColor targetColor, qreal percentage);

public:
    bool isValid();

public:
    friend LIBQTEXTENSIONS_EXPORT QDataStream & operator << (QDataStream & out, const zcColor & col);
    friend LIBQTEXTENSIONS_EXPORT QDataStream & operator << (QDataStream & out, const zcColor * col);
    friend LIBQTEXTENSIONS_EXPORT QDataStream & operator >> (QDataStream & out, zcColor & col);
    friend LIBQTEXTENSIONS_EXPORT QDataStream & operator >> (QDataStream & out, zcColor * col);

    QJsonObject toJson() const;
    void fromJson(const QJsonObject & obj);

public:
    zcColor & operator =(const QColor & c) {
        super::operator =(c);
        return *this;
    }

};

#endif // ZCCOLOR_H
