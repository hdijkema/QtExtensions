#ifndef ZCHTMLMENUICONENGINE_H
#define ZCHTMLMENUICONENGINE_H

#include <QIconEngine>

#ifndef QT6
#  if (QT_VERSION >= QT_VERSION_CHECK(6, 0, 0))
#    define QT6
#  endif
#endif

class zcHtmlMenuIconEngine : public QIconEngine
{
public:
    zcHtmlMenuIconEngine();

    // QIconEngine interface
public:
    virtual void paint(QPainter *painter, const QRect &rect, QIcon::Mode mode, QIcon::State state) override;
    virtual QIconEngine *clone() const override;
    virtual void virtual_hook(int id, void *data) override;

#ifdef QT6
    // QIconEngine interface
public:
    virtual QString iconName() override;
#endif
};

#endif // ZCHTMLMENUICONENGINE_H
