#ifndef ZCPREFSPROVIDER_H
#define ZCPREFSPROVIDER_H

#include <QObject>
#include <QVariant>
#include <QDate>
#include <QDateTime>
#include <QColor>
#include "zccolor.h"

#define zcpp_decl(type, op) \
    type get(const QString &key, const type &dv) { return vget(key, dv).op(); } \
    void set(const QString &key, const type &dv) { vset(key, dv); }

#define zcpp_decl1(type, cvt_to, cvt_from) \
    type get(const QString &key, const type &dv) { cvt_from(vget(key, cvt_to(dv))); } \
    void set(const QString &key, const type &dv) { vset(key, cvt_to(dv)); }

class zcPrefsProvider : public QObject
{
    Q_OBJECT
public:
    class Funcs {
    public:
        virtual QVariant get(const QString &key, const QVariant &default_value);
        virtual void set(const QString &key, const QVariant &value);
        virtual void del(const QString &key);
    public:
        virtual ~Funcs();
    };

private:
    Funcs   _funcs;

public:
    void setFuncs(Funcs funcs);

public:
    explicit zcPrefsProvider(QObject *parent = nullptr);
    explicit zcPrefsProvider(Funcs funcs, QObject *parent = nullptr);
   ~zcPrefsProvider();

public:
    QVariant vget(const QString &key, const QVariant &default_value);
    void vset(const QString &key, const QVariant &value);
    void del(const QString &key);

public:
    zcpp_decl(QString, toString)
    zcpp_decl(int, toInt)
    zcpp_decl(double, toDouble)
    zcpp_decl(long long, toLongLong)
    zcpp_decl(unsigned int, toUInt)
    zcpp_decl(unsigned long long, toULongLong)
    zcpp_decl(QDate, toDate)
    zcpp_decl(QDateTime, toDateTime)
    zcpp_decl1(QColor, [](QColor c) { zcColor f(c); return f.toHTML(); }, [](const QVariant &c){ return zcColor(c.toString()); })
    zcpp_decl1(zcColor, [](zcColor c) { return c.toHTML(); }, [](const QVariant &c) { return zcColor(c.toString()); })
};

#undef zcpp_decl
#undef zcpp_decl1

#endif // ZCPREFSPROVIDER_H
