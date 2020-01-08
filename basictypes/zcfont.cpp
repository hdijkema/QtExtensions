#include "zcfont.h"
#include <QFontInfo>
#include "zclib_defaults.h"

zcFont::zcFont()
{
}

zcFont::zcFont(const QFont &font) : QFont(font)
{
}

zcFont::zcFont(int pt)
{
    super::setPointSize(pt);
}

zcFont::zcFont(const QString &family, int pt)
{
    super::setFamily(family);
    super::setPointSize(pt);
}

QJsonObject zcFont::toJson() const
{
    QFontInfo info(*this);
    QJsonObject obj;
    obj["type"] = QString("zcFont");
    obj["version"] = 1;
    obj["family"] = info.family();
    obj["pointSize"] = info.pointSizeF();
    obj["italic"] = info.italic();
    obj["bold"] = info.bold();
    return obj;
}

zcFont zcFont::deriveScaled(qreal factor) const
{
    zcFont f(*this);
    f.setPointSizeF(this->pointSizeF() * factor);
    return f;
}

QDataStream & operator << (QDataStream & out, const zcFont & f) {
    out << ZCFONT_MAGIC(1);
    QFontInfo info(f);
    out << f.family();
    out << f.pointSizeF();
    out << f.italic();
    out << f.bold();
    return out;
}

QDataStream & operator << (QDataStream & out, const zcFont * f) {
    return operator <<(out, *f);
}

void zcFont::fromJson(const QJsonObject &obj) {
    QFont f;
    f.setFamily(obj["family"].toString());
    f.setPointSizeF(obj["pointSize"].toDouble());
    f.setBold(obj["bold"].toBool());
    f.setItalic(obj["italic"].toBool());
    *this = f;
}

QDataStream & operator >> (QDataStream & in, zcFont & f) {
    MAGIC_ASSERT(in, ZCFONT_TYPE, 1);
    QString family;
    qreal pointSize;
    bool italic;
    bool bold;

    in >> family;
    in >> pointSize;
    in >> italic;
    in >> bold;

    f.setFamily(family);
    f.setPointSizeF(pointSize);
    f.setBold(bold);
    f.setItalic(italic);

    return in;
}

QDataStream & operator >> (QDataStream & in, zcFont * f) {
    return operator >>(in, *f);
}
