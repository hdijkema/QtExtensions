#include "zchtmlmenuiconengine.h"

zcHtmlMenuIconEngine::zcHtmlMenuIconEngine()
{
}

void zcHtmlMenuIconEngine::paint(QPainter *, const QRect &, QIcon::Mode , QIcon::State )
{
    // does nothing
}

QIconEngine *zcHtmlMenuIconEngine::clone() const
{
    return new zcHtmlMenuIconEngine();
}

void zcHtmlMenuIconEngine::virtual_hook(int id, void *data)
{
    if (id == QIconEngine::IsNullHook) {
        bool *b = reinterpret_cast<bool *>(data);
        *b = true;
    }
#ifndef QT6
    else if (id == QIconEngine::IconNameHook) {
        QString *name = reinterpret_cast<QString *>(data);
        *name = "zcHtmlMenuIcon";
    }
#endif
}

#ifdef QT6
QString zcHtmlMenuIconEngine::iconName()
{
    return "zcHtmlMenuIcon";
}
#endif

