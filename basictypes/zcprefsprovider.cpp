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

void zcPrefsProvider::setFuncs(zcPrefsProvider::Funcs funcs)
{
    _funcs = funcs;
}

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
