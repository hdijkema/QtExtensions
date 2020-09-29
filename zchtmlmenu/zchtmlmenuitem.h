#ifndef INTERNAL_ZCHTMLMENUITEM_H
#define INTERNAL_ZCHTMLMENUITEM_H
/**

    This file is part of QtExtensions (https://github.com/hdijkema/QtExtensions).

    (c) Hans Dijkema 2020

    QtExtensions is free software: you can redistribute it and/or modify
    it under the terms of the GNU Lesser General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    Foobar is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU Lesser General Public License
    along with QtExtensions. If not, see <https://www.gnu.org/licenses/lgpl.html>.

**/

#include <QWidget>
#include <QMenu>
#include <QLabel>
#include <QIcon>

class zcHtmlMenu;

class internal_zcHtmlMenuItem : public QWidget
{
    Q_OBJECT
private:
    zcHtmlMenu    *_my_menu;
    QLabel       *_label;
    QLabel       *_l_icon;

public:
    internal_zcHtmlMenuItem(zcHtmlMenu *parent);
    internal_zcHtmlMenuItem(const QString &html_label, zcHtmlMenu *parent);
    internal_zcHtmlMenuItem(const QIcon &icn, const QString &html_label, zcHtmlMenu *parent);

public:
    ~internal_zcHtmlMenuItem();

public:
    void setHtml(const QString &html);
    void setIcon(const QIcon &icon);

    // QWidget interface
protected:
    void enterEvent(QEvent *event) override;
    void leaveEvent(QEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;

signals:
    void clicked();

    // QWidget interface
protected:
    void paintEvent(QPaintEvent *event) override;
};

#endif // INTERNAL_ZCHTMLMENUITEM_H
