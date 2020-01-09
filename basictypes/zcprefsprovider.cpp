#include "zcprefsprovider.h"

static QHash<QString, QVariant> _store;

class MyFuncs : public zcPrefsProvider::Funcs
{
    // Funcs interface
public:
    QVariant get(const QString &key, const QVariant &default_value) override {
        if (_store.contains(key)) {
            return _store[key];
        } else {
            return default_value;
        }
    }

    void set(const QString &key, const QVariant &value) override {
        _store.insert(key, value);
    }

    void del(const QString &key) override {
        _store.remove(key);
    }
};

zcPrefsProvider::zcPrefsProvider(QObject *parent) :
    zcPrefsProvider(MyFuncs(), parent)
{
}

zcPrefsProvider::zcPrefsProvider(zcPrefsProvider::Funcs funcs, QObject *parent)
    : QObject(parent)
{
    _funcs = funcs;
}

zcPrefsProvider::~zcPrefsProvider()
{
}

void zcPrefsProvider::setFuncs(zcPrefsProvider::Funcs funcs)
{
    _funcs = funcs;
}


#define zcpp_decl(type, op) \
    type zcPrefsProvider::get(const QString &key, const type &dv) { return vget(key, dv).op(); } \
    void zcPrefsProvider::set(const QString &key, const type &dv) { vset(key, dv); }

#define zcpp_decl1(type, cvt_to, cvt_from) \
    type zcPrefsProvider::get(const QString &key, const type &dv) { return cvt_from(vget(key, cvt_to(dv))); } \
    void zcPrefsProvider::set(const QString &key, const type &dv) { vset(key, cvt_to(dv)); }

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



QVariant zcPrefsProvider::vget(const QString &key, const QVariant &default_value)
{
    return _funcs.get(key, default_value);
}

void zcPrefsProvider::vset(const QString &key, const QVariant &value)
{
    _funcs.set(key, value);
}

void zcPrefsProvider::del(const QString &key)
{
    _funcs.del(key);
}

QVariant zcPrefsProvider::Funcs::get(const QString &, const QVariant &default_value)
{
    return default_value;
}

void zcPrefsProvider::Funcs::set(const QString &, const QVariant &)
{
    // does nothing
}

void zcPrefsProvider::Funcs::del(const QString &)
{
    // does nothing
}

zcPrefsProvider::Funcs::~Funcs()
{
    // Does nothing
}
