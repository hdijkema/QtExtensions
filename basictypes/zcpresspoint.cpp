#include "zcpresspoint.h"
#include "zclib_defaults.h"

QJsonObject zcPressPoint::toJson() const
{
    QJsonObject obj;
    obj["x"] = this->x();
    obj["y"] = this->y();
    obj["p"] = this->pressure();
    return obj;
}

QDataStream & operator << (QDataStream & out, const zcPressPoint & p) {
    out << PRESSPOINT_MAGIC(1);
    out << p.x();
    out << p.y();
    out << p.pressure();
    return out;
}

QDataStream & operator << (QDataStream & out, const zcPressPoint * p) {
    return operator <<(out, *p);
}

void zcPressPoint::fromJson(const QJsonObject &obj) {
    this->setX(obj["x"].toDouble());
    this->setY(obj["y"].toDouble());
    if (obj["pressure"].isDouble()) {
        this->setPressure(obj["pressure"].toDouble());
    } else {
        this->setPressure(obj["p"].toDouble());
    }
}

QDataStream & operator >> (QDataStream & in, zcPressPoint & pr) {
    MAGIC_ASSERT(in, PRESSPOINT_TYPE, 1);
    qreal x, y, p;
    in >> x;
    in >> y;
    in >> p;
    pr.setX(x);
    pr.setY(y);
    pr.setPressure(p);
    return in;
}

QDataStream & operator >> (QDataStream & in, zcPressPoint * p) {
    return operator >>(in, *p);
}

