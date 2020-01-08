#ifndef QHTMLMENU_H
#define QHTMLMENU_H

#include "libqtextensions_global.h"

#include <QMenu>
#include <QHash>
#include <QAction>

class internal_QHtmlMenuItem;

#ifdef Q_QDOC
class QHtmlMenu : public QMenu
#else
class LIBQTEXTENSIONS_EXPORT QHtmlMenu : public QMenu
#endif
{
    Q_OBJECT
private:
    QHash<QWidget *, QAction *>                  _actions;
    QHash<QAction *, internal_QHtmlMenuItem *>   _items;
    QAction                                     *_current_action;
    int                                          _action_h_margin;
    int                                          _action_v_margin;
    int                                          _action_icon_size;
    int                                          _text_height;

public:
    QHtmlMenu(const QString &title, QWidget *parent = nullptr);
    QHtmlMenu(QWidget *parent = nullptr);

public:
    QAction *addHtmlAction(const QIcon &icon, const QString &html_label);
    QAction *addHtmlAction(const QString &html_label);
    QAction *insertHtmlAction(QAction *before, const QIcon &icon, const QString &html_label);
    QAction *insertHtmlAction(QAction *before, const QString &html_label);

public:

public:
    QAction *exec();
    QAction *exec(const QPoint &pos, QAction *action = nullptr);

private:
    QFont drawBackground(QPainter &p, const QRect &rect, bool hovered, internal_QHtmlMenuItem *item);
    void setActiveHtmlItem(internal_QHtmlMenuItem *item);
    bool isActiveHtmlItem(internal_QHtmlMenuItem *item);
    QAction *createHtmlAction(const QIcon &icon, const QString &html_label);

private slots:
    void htmlActionTriggered();
    void htmlActionChanged();

public:
    static int version_major();
    static int version_minor();
    static QString version();

public:
    friend class internal_QHtmlMenuItem;
};


#endif // QHTMLMENU_H
