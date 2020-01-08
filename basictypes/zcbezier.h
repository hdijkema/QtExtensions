#ifndef BEZIER_H
#define BEZIER_H

#include <QPointF>
#include <QRectF>
#include <QDebug>
#include <QJsonObject>
#include <QDataStream>

#include "zcpresspoint.h"
#include "libqtextensions_global.h"

class LIBQTEXTENSIONS_EXPORT zcBezier {

private:
    QPointF _start;
    QPointF _control1;
    QPointF _control2;
    QPointF _end;
    qreal   _startPressure;
    qreal   _endPressure;

private:
    inline qreal min(qreal a, qreal b) { return (a < b) ? a : b; }
    inline qreal max(qreal a, qreal b) { return (a > b) ? a : b; }

public:
    zcBezier() {
        _start = QPointF(0.0, 0.0);
        _end = QPointF(0.0, 0.0);
        _control1 = QPointF(0.0, 0.0);
        _control2 = QPointF(0.0, 0.0);
        _startPressure = 0.0;
        _endPressure = 0.0;
    }

    zcBezier(QPointF & start, QPointF & c1, QPointF & c2, QPointF end,
           qreal startPressure, qreal endPressure) {
        _start = start;
        _control1 = c1;
        _control2 = c2;
        _end = end;
        _startPressure = startPressure;
        _endPressure = endPressure;
    }

    QPointF & startPt()         { return _start; }
    QPointF & control1Pt()      { return _control1; }
    QPointF & control2Pt()      { return _control2; }
    QPointF & endPt()           { return _end; }
    qreal startPressure()       { return _startPressure; }
    qreal endPressure()         { return _endPressure; }

    const QPointF & startPt() const   { return _start; }
    const QPointF & control1Pt() const{ return _control1; }
    const QPointF & control2Pt() const{ return _control2; }
    const QPointF & endPt() const     { return _end; }
    qreal startPressure() const       { return _startPressure; }
    qreal endPressure() const         { return _endPressure; }

    void setStartPt(qreal pressure, const QPointF & p)  { _startPressure = pressure; _start = p; }
    void setC1Pt(const QPointF & c1)                    { _control1 = c1; }
    void setC2Pt(const QPointF & c2)                    { _control2 = c2; }
    void setEndPt(qreal pressure, const QPointF & p)    { _endPressure = pressure; _end = p; }
    void setStartPt(const zcPressPoint & p)               { _startPressure = p.pressure(); _start = p.point(); }
    void setEndPt(const zcPressPoint & p)                 { _endPressure = p.pressure(); _end = p.point(); }

    void addDy(qreal dyPt);

    QPointF & operator[](int i) {
        switch(i) {
            case 0: return startPt();
            case 1: return control1Pt();
            case 2: return control2Pt();
            case 3: return endPt();
            default: throw("Bezier has index 0 .. 3");
        }
        //return startPt();
    }

    const QPointF & operator[](int i) const {
        switch(i) {
            case 0: return startPt();
            case 1: return control1Pt();
            case 2: return control2Pt();
            case 3: return endPt();
            default: throw("Bezier has index 0 .. 3");
        }
        //return startPt();
    }

    QRectF rectPt() {
        qreal pr = max(_endPressure, _startPressure);
        qreal leftX = min(_start.x(), min(_control1.x(), min(_control2.x(), _end.x()))) - 2.0 * pr;
        qreal topY = min(_start.y(), min(_control1.y(), min(_control2.y(), _end.y()))) - 2.0 * pr;
        qreal rightX = max(_start.x(), max(_control1.x(), max(_control2.x(), _end.x()))) + 2.0 * pr;
        qreal bottomY = max(_start.y(), max(_control1.y(), max(_control2.y(), _end.y()))) + 2.0 * pr;
        QRectF r(QPointF(leftX, topY), QPointF(rightX, bottomY));
        return r;
    }

    qreal length();

public:
    QJsonObject toJson() const;
    friend LIBQTEXTENSIONS_EXPORT QDataStream & operator << (QDataStream & out, const zcBezier & b);
    friend LIBQTEXTENSIONS_EXPORT QDataStream & operator << (QDataStream & out, const zcBezier * p);

    void fromJson(const QJsonObject & obj);
    friend LIBQTEXTENSIONS_EXPORT QDataStream & operator >> (QDataStream & out, zcBezier & b);
    friend LIBQTEXTENSIONS_EXPORT QDataStream & operator >> (QDataStream & out, zcBezier * p);

public:
    friend LIBQTEXTENSIONS_EXPORT QDebug & operator<< (QDebug & d, const zcBezier & input);
};

#endif // BEZIER_H
