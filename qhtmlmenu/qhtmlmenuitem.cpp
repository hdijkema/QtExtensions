#include "qhtmlmenuitem.h"

#include <QPainter>
#include <QMenu>
#include <QStyleOptionMenuItem>
#include <QMouseEvent>
#include <QHBoxLayout>

#include "qhtmlmenu.h"
#include "qhtmlmenuitemlabel.h"


internal_QHtmlMenuItem::internal_QHtmlMenuItem(QHtmlMenu *parent)
    : internal_QHtmlMenuItem("", parent)
{
}

internal_QHtmlMenuItem::internal_QHtmlMenuItem(const QString &html_label, QHtmlMenu *parent)
    : internal_QHtmlMenuItem(QIcon(), html_label, parent)
{
}

internal_QHtmlMenuItem::internal_QHtmlMenuItem(const QIcon &icn, const QString &html_label, QHtmlMenu *parent)
    : QWidget(parent), _my_menu(parent)
{
    _label = new internal_QHtmlMenuItemLabel(this);
    _l_icon = new internal_QHtmlMenuItemLabel(this);

    QHBoxLayout *hbox = new QHBoxLayout();
    hbox->setContentsMargins(0, 0, 0, 0);

    hbox->addWidget(_l_icon);
    hbox->addWidget(_label, 1);

    setLayout(hbox);

    setIcon(icn);
    setHtml(html_label);
}

void internal_QHtmlMenuItem::setHtml(const QString &html_label)
{
    _label->setText(html_label);
}

void internal_QHtmlMenuItem::setIcon(const QIcon &icn)
{
    QStyle *style = _my_menu->style();
    QStyleOption opt;
    opt.init(this);
    int icone = style->pixelMetric(QStyle::PM_SmallIconSize, &opt, this);

    _l_icon->setPixmap(icn.pixmap(QSize(icone, icone)));
}

void internal_QHtmlMenuItem::enterEvent(QEvent *)
{
    _my_menu->setActiveHtmlItem(this);
    update();
}

void internal_QHtmlMenuItem::leaveEvent(QEvent *)
{
    _my_menu->setActiveHtmlItem(nullptr);
    update();
}

void internal_QHtmlMenuItem::mouseReleaseEvent(QMouseEvent *event)
{
    emit clicked();
    event->ignore(); // Ignore this event here and the popup menu will disappear.
                     // It means we don't handle the event, which will make
                     // the parent widget (QMenu) handle it.
}

void internal_QHtmlMenuItem::paintEvent(QPaintEvent *event)
{
    QPainter p(this);

    bool hovered = _my_menu->isActiveHtmlItem(this);
    QFont f = _my_menu->drawBackground(p, rect(), hovered, this);

    _label->setFont(f);
    QWidget::paintEvent(event);
}
