#ifndef ZCFONT_H
#define ZCFONT_H

#include <QFont>
#include <QJsonObject>
#include <QDataStream>

#include "libqtextensions_global.h"

class LIBQTEXTENSIONS_EXPORT zcFont : public QFont
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
