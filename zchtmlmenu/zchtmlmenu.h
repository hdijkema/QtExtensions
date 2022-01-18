#ifndef ZCHTMLMENU_H
#define ZCHTMLMENU_H
/**

    This file is part of QtExtensions (https://github.com/hdijkema/QtExtensions).

    (c) Hans Dijkema 2020

    QtExtensions is free software: you can redistribute it and/or modify
    it under the terms of the GNU Lesser General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    Qtextensions is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU Lesser General Public License
    along with QtExtensions. If not, see <https://www.gnu.org/licenses/lgpl.html>.

**/

#include "libqtextensions_global.h"

#include <QMenu>
#include <QHash>
#include <QAction>

class internal_zcHtmlMenuItem;

#ifdef Q_QDOC
class zcHtmlMenu : public QMenu
#else
class LIBQTEXTENSIONS_EXPORT zcHtmlMenu : public QMenu
#endif
{
    Q_OBJECT
private:
    QHash<QWidget *, QAction *>                  _actions;
    QHash<QAction *, internal_zcHtmlMenuItem *>  _items;
    QAction                                     *_current_action;
    int                                          _action_h_margin;
    int                                          _action_v_margin;
    int                                          _action_icon_size;
    int                                          _text_height;

public:
    explicit zcHtmlMenu(const QString &title, QWidget *parent = nullptr);
    zcHtmlMenu(QWidget *parent = nullptr);

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
    QFont drawBackground(QPainter &p, const QRect &rect, bool hovered, internal_zcHtmlMenuItem *item);
    void setActiveHtmlItem(internal_zcHtmlMenuItem *item);
    bool isActiveHtmlItem(internal_zcHtmlMenuItem *item);
    QAction *createHtmlAction(const QIcon &icon, const QString &html_label);

private slots:
    void htmlActionTriggered();
    void htmlActionChanged();

public:
    static int version_major();
    static int version_minor();
    static QString version();

public:
    friend class internal_zcHtmlMenuItem;
};


#endif // ZCHTMLMENU_H
