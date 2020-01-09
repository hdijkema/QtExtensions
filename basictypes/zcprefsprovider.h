#ifndef ZCPREFSPROVIDER_H
#define ZCPREFSPROVIDER_H

#include <QObject>
#include <QVariant>
#include <QDate>
#include <QDateTime>
#include <QColor>
#include "zccolor.h"

#define zcpp_decl(type) \
    type get(const QString &key, const type &dv); \
    void set(const QString &key, const type &dv);

#ifdef Q_QDOC
class zcPrefsProvider : public QObject
#else
class LIBQTEXTENSIONS_EXPORT zcPrefsProvider : public QObject
#endif
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
    zcpp_decl(QString)
    zcpp_decl(int)
    zcpp_decl(double)
    zcpp_decl(long long)
    zcpp_decl(unsigned int)
    zcpp_decl(unsigned long long)
    zcpp_decl(QDate)
    zcpp_decl(QDateTime)
    zcpp_decl(QColor)
    zcpp_decl(zcColor)
};

#undef zcpp_decl

#endif // ZCPREFSPROVIDER_H
