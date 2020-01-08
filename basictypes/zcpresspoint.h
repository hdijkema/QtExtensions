#ifndef PRESSPOINT_H
#define PRESSPOINT_H

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
    friend QDataStream & operator << (QDataStream & out, const zcPressPoint & p);
    friend QDataStream & operator << (QDataStream & out, const zcPressPoint * p);
    friend QDataStream & operator >> (QDataStream & in, zcPressPoint & p);
    friend QDataStream & operator >> (QDataStream & in, zcPressPoint * p);
    void fromJson(const QJsonObject &obj);
};


#endif // PRESSPOINT_H
