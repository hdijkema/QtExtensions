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
#include "zccolor.h"
#include <QRgb>
#include "zclib_defaults.h"
#include <stdlib.h>

zcColor::zcColor(const QColor &col) : QColor(col) {
    _invalid = false;
}

zcColor::zcColor(int color) : QColor(static_cast<QRgb>(color)) {
    _invalid = false;
}

zcColor::zcColor(int r, int g, int b, int a) : QColor(r, g, b, a)
{
    _invalid = false;
}

zcColor::zcColor(const char *htmlColor) : QColor(zcColor::fromHTML(htmlColor))
{
    _invalid = false;
}

zcColor zcColor::invalidColor()
{
    zcColor c;
    c._invalid = true;
    return c;
}

zcColor zcColor::fromHTML(const QString &htmlColor)
{
    QString c(htmlColor);
    c.replace("#", "");
    bool ok;
    int alpha = 255;
    if (c.length() == 8) {
        alpha = c.mid(6).toInt(&ok, 16);
    }
    int col = c.mid(0, 6).toInt(&ok, 16);
    int r = col / 65536;
    int g = (col / 256) & 0xff;
    int b = col & 0xff;
    return zcColor(r, g, b, alpha);
}

QString zcColor::toHTML() const
{
    char buf[100];
    if (this->alpha() != 255) {
        sprintf(buf, "%02x%02x%02x%02x", this->red(), this->green(), this->blue(), this->alpha());
    } else {
        sprintf(buf, "%02x%02x%02x", this->red(), this->green(), this->blue());
    }
    QString str(buf);
    return "#"+str;
}

qint32 zcColor::toIntRgb() const
{
    QRgb rgb = this->rgb();
    return static_cast<qint32>(rgb);
}

bool zcColor::equals(QColor other)
{
    if (other.alpha() == 0 && this->alpha() == 0) {
        return true;    // allebei helemaal doorzichtig.
    }

    return other.alpha() == this->alpha() &&
            other.red() == this->red() &&
            other.green() == this->green() &&
            other.blue() == this->blue();
}

bool zcColor::isTransparent()
{
    return this->alpha() == 0;
}

void zcColor::interpolateTo(zcColor targetColor, qreal percentage)
{
    qreal r = red();
    qreal g = green();
    qreal b = blue();

    qreal p = percentage / 100.0;
    setRed(static_cast<int>(r * (1 - p) + targetColor.red() * p));
    setGreen(static_cast<int>(g * (1 - p) + targetColor.green() * p));
    setBlue(static_cast<int>(b * (1 - p) + targetColor.blue() * p));
}

bool zcColor::isValid()
{
    return !_invalid;
}

QJsonObject zcColor::toJson() const {
    QJsonObject obj;
    //obj["type"] = QString("zcColor");
    //obj["version"] = 1;
    QRgb rgba = this->rgba();
    obj["rgba"] = static_cast<int>(rgba);
    return obj;
}

void zcColor::fromJson(const QJsonObject & obj) {
    if (obj.contains("rgba")) {
        this->setRgba(static_cast<QRgb>(obj["rgba"].toInt()));
    }
}

LIBQTEXTENSIONS_EXPORT QDataStream & operator << (QDataStream & out, const zcColor & col) {
    out << ZCCOLOR_MAGIC(1);
    QRgb rgba = col.rgba();
    qint32 c = static_cast<qint32>(rgba);
    out << c;
    return out;
}

LIBQTEXTENSIONS_EXPORT QDataStream & operator << (QDataStream & out, const zcColor * col) {
    return operator <<(out, *col);
}

LIBQTEXTENSIONS_EXPORT QDataStream & operator >> (QDataStream & in, zcColor & col) {
    MAGIC_ASSERT(in, ZCCOLOR_TYPE, 1);
    qint32 c;
    in >> c;
    col.setRgba(static_cast<QRgb>(c));
    return in;
}

LIBQTEXTENSIONS_EXPORT QDataStream & operator >> (QDataStream & in, zcColor * col) {
    return operator >>(in, *col);
}





