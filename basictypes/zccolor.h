#ifndef ZCCOLOR_H
#define ZCCOLOR_H

#include <QColor>
#include <QJsonObject>
#include <QDataStream>

#include "libqtextensions_global.h"

class LIBQTEXTENSIONS_EXPORT zcColor : public QColor
{
private:
    typedef QColor super;
    bool _invalid;

public:
    explicit zcColor(const QColor & col);
    explicit zcColor(int color = Qt::black);
    explicit zcColor(int r, int g, int b, int a = 255);
    explicit zcColor(const char *htmlColor);

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
