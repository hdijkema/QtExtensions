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

#include "zchtmlmenuitem.h"

#include <QPainter>
#include <QMenu>
#include <QStyleOptionMenuItem>
#include <QMouseEvent>
#include <QHBoxLayout>

#include "zchtmlmenu.h"
#include "zchtmlmenuitemlabel.h"

#include <QDebug>


internal_zcHtmlMenuItem::internal_zcHtmlMenuItem(zcHtmlMenu *parent)
    : internal_zcHtmlMenuItem("", parent)
{
}

internal_zcHtmlMenuItem::internal_zcHtmlMenuItem(const QString &html_label, zcHtmlMenu *parent)
    : internal_zcHtmlMenuItem(QIcon(), html_label, parent)
{
}

internal_zcHtmlMenuItem::internal_zcHtmlMenuItem(const QIcon &icn, const QString &html_label, zcHtmlMenu *parent)
    : QWidget(parent), _my_menu(parent)
{
    _label = new internal_zcHtmlMenuItemLabel(this);
    _l_icon = new internal_zcHtmlMenuItemLabel(this);

    QHBoxLayout *hbox = new QHBoxLayout();
    hbox->setContentsMargins(0, 0, 0, 0);

    hbox->addWidget(_l_icon);
    hbox->addWidget(_label, 1);

    setLayout(hbox);

    setIcon(icn);
    setHtml(html_label);
}

internal_zcHtmlMenuItem::~internal_zcHtmlMenuItem()
{
    _my_menu = nullptr;
}

void internal_zcHtmlMenuItem::setHtml(const QString &html_label)
{
    _label->setText(html_label);
}

void internal_zcHtmlMenuItem::setIcon(const QIcon &icn)
{
    QStyle *style = _my_menu->style();
    QStyleOption opt;
    opt.init(this);
    int icone = style->pixelMetric(QStyle::PM_SmallIconSize, &opt, this);

    _l_icon->setPixmap(icn.pixmap(QSize(icone, icone)));
}

void internal_zcHtmlMenuItem::enterEvent(QEvent *)
{
    if (_my_menu != nullptr) {
        _my_menu->setActiveHtmlItem(this);
        update();
    } else {
        qDebug() << "Unexpected! _my_menu == nullptr!";
    }
}

void internal_zcHtmlMenuItem::leaveEvent(QEvent *)
{
    if (_my_menu != nullptr) {
        _my_menu->setActiveHtmlItem(nullptr);
        update();
    } else {
        qDebug() << "Unexpected! _my_menu == nullptr!";
    }
}

void internal_zcHtmlMenuItem::mouseReleaseEvent(QMouseEvent *event)
{
    emit clicked();
    event->ignore(); // Ignore this event here and the popup menu will disappear.
                     // It means we don't handle the event, which will make
                     // the parent widget (QMenu) handle it.
}

void internal_zcHtmlMenuItem::paintEvent(QPaintEvent *event)
{
    QPainter p(this);

    bool hovered = _my_menu->isActiveHtmlItem(this);
    QFont f = _my_menu->drawBackground(p, rect(), hovered, this);

    _label->setFont(f);
    QWidget::paintEvent(event);
}
