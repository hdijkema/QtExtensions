#ifndef ZCHTMLMENUICONENGINE_H
#define ZCHTMLMENUICONENGINE_H

#include <QIconEngine>

class zcHtmlMenuIconEngine : public QIconEngine
{
public:
    zcHtmlMenuIconEngine();

    // QIconEngine interface
public:
    void paint(QPainter *painter, const QRect &rect, QIcon::Mode mode, QIcon::State state);
    QIconEngine *clone() const;
    void virtual_hook(int id, void *data);
};

#endif // ZCHTMLMENUICONENGINE_H
