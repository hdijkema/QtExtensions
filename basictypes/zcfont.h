#ifndef ZCFONT_H
#define ZCFONT_H
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

#include "libqtextensions_global.h"
#include <QFont>
#include <QJsonObject>
#include <QDataStream>


#ifdef Q_QDOC
class zcFont : public QFont
#else
class LIBQTEXTENSIONS_EXPORT zcFont : public QFont
#endif
{
private:
    typedef QFont super;
public:
    zcFont();
    zcFont(const QFont & font);
    zcFont(int pt);
    zcFont(const QString & family, int pt);

public:
    friend LIBQTEXTENSIONS_EXPORT QDataStream & operator << (QDataStream & out, const zcFont & f);
    friend LIBQTEXTENSIONS_EXPORT QDataStream & operator << (QDataStream & out, const zcFont * f);
    friend LIBQTEXTENSIONS_EXPORT QDataStream & operator >> (QDataStream & in, zcFont & f);
    friend LIBQTEXTENSIONS_EXPORT QDataStream & operator >> (QDataStream & in, zcFont * f);

    void fromJson(const QJsonObject & obj);
    QJsonObject toJson() const;

    zcFont deriveScaled(qreal factor) const;

public:
    zcFont & operator = (const QFont &f) { super::operator =(f);return *this; }
};

#endif // ZCFONT_H
