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

#include "zchtmlmenu.h"

#include <QWidgetAction>
#include <QStyleOptionMenuItem>

#include "zchtmlmenu.h"
#include "zchtmlmenuitem.h"

#define zcHtmlMenu_VERSION_MAJOR 0
#define zcHtmlMenu_VERSION_MINOR 1

/*!
    \class zcHtmlMenu
    \inmodule QtExtensions

    \brief The zcHtmlMenu class provides a menu widget based on QMenu for use in menu
    bars, context menus, and other popup menus. It supports the QLabel Html subset.

    \section1 Actions

    zcHtmlMenu extends QMenu with extra functions to add actions:

    addHtmlAction() and insertHtmlAction() functions.

    See also \l {http://doc.qt.io/qt-5/qmenu.html} {QMenu}

    \section1 Example

    \code
      (...)

      zcHtmlMenu *popup = new zcHtmlMenu(tr("Insert texts"), this);

      QAction *a1 = popup->addAction(tr("Normal action 1"));
      QAction *a2 = popup->addHtmlAction(tr("<b>Bold text</b> to be inserted"));
      QAction *a3 = popup->addHtmlAction(tr("<i>Italic text</i> to be inserted"));

      QAction *choosen_action = popup->exec(QCursor::pos());

      if (choosen_action == a1) { / * do something * / }
      else if (choosen_action == a2) { / * insert bold text * / }
      else if (choosen_action == a3) { / * insert italic text * / }

      popup->deleteLater();

      (...)
    \endcode
*/

/*!
    \brief Creates a zcHtmlMenu with an empty title and given parent \a parent
 */
zcHtmlMenu::zcHtmlMenu(QWidget *parent)
    : zcHtmlMenu("", parent)
{
}

/*!
    \brief Creates a zcHtmlMenu with the given title \a title and parent \a parent
*/
zcHtmlMenu::zcHtmlMenu(const QString &title, QWidget *parent)
    : QMenu(title, parent)
{
    _current_action = nullptr;

    QStyle *style = this->style();
    QStyleOption opt;
    opt.init(this);
    int hmargin = style->pixelMetric(QStyle::PM_MenuHMargin, &opt, this);
    int vmargin = style->pixelMetric(QStyle::PM_MenuVMargin, &opt, this);
    int icone = style->pixelMetric(QStyle::PM_SmallIconSize, &opt, this);

    _action_h_margin = hmargin;
    _action_v_margin = vmargin;
    _action_icon_size = icone;

    QSize s(0, 0);
    QStyleOptionMenuItem t_opt;
    QAction a("");
    initStyleOption(&t_opt, &a);
    s = style->sizeFromContents(QStyle::CT_MenuItem, &t_opt, s, this);

    _text_height = s.height();
}

/*!
 * \brief Adds an action to the menu with the given \a icon and \a html_label.
 *
 *
 * \return The returned action can be modified using \l {https://doc.qt.io/qt-5/qaction.html#icon-prop} {setIcon()}
 * and \l {https://doc.qt.io/qt-5/qaction.html#text-prop} {setTitle()}, see \l{https://doc.qt.io/qt-5/qaction.html} {QAction}.
 * These are the only ones supported by this class.
 */
QAction *zcHtmlMenu::addHtmlAction(const QIcon &icon, const QString &html_label)
{
    QWidgetAction *wa = qobject_cast<QWidgetAction *>(createHtmlAction(icon, html_label));
    internal_zcHtmlMenuItem *item = qobject_cast<internal_zcHtmlMenuItem *>(wa->defaultWidget());

    addAction(wa);
    _actions.insert(item, wa);
    _items.insert(wa, item);

    return wa;
}

/*!
 * \brief Convenience function for addHtmlAction() with empty icon and \a html_label.
 */
QAction *zcHtmlMenu::addHtmlAction(const QString &html_label)
{
    return addHtmlAction(QIcon(), html_label);
}


/*!
 * \brief Inserts a new action before \a before, based on \a icon and \a html_label.
 *
 * \return zcHtmlMenu takes ownership of the returned QAction.
 * For Supported properties of the returned QAction, see addHtmlAction()
 */
QAction *zcHtmlMenu::insertHtmlAction(QAction *before, const QIcon &icon, const QString &html_label)
{
    QWidgetAction *wa = qobject_cast<QWidgetAction *>(createHtmlAction(icon, html_label));
    internal_zcHtmlMenuItem *item = qobject_cast<internal_zcHtmlMenuItem *>(wa->defaultWidget());

    insertAction(before, wa);
    _actions.insert(item, wa);
    _items.insert(wa, item);

    return wa;
}

/*!
 * \brief Convenience function for insertHtmlAction() with empty icon, \a before and \a html_label.
 */
QAction *zcHtmlMenu::insertHtmlAction(QAction *before, const QString &html_label)
{
    return insertHtmlAction(before, QIcon(), html_label);
}



QAction *zcHtmlMenu::createHtmlAction(const QIcon &icon, const QString &html_label)
{
    internal_zcHtmlMenuItem *item = new internal_zcHtmlMenuItem(icon, html_label, this);
    int hmargin = _action_h_margin;
    int vmargin = _action_v_margin;
    int height = _text_height;

    item->setContentsMargins(hmargin, vmargin, hmargin, vmargin);
    item->setMinimumHeight(height);

    QWidgetAction *wa = new QWidgetAction(this);
    wa->setDefaultWidget(item);

    wa->setIcon(icon);
    wa->setText(html_label);

    connect(wa, &QWidgetAction::triggered, this, &zcHtmlMenu::htmlActionTriggered);
    connect(wa, &QAction::changed, this, &zcHtmlMenu::htmlActionChanged);

    return wa;
}


QAction *zcHtmlMenu::exec()
{
    return exec(pos());
}

QAction *zcHtmlMenu::exec(const QPoint &pos, QAction *action)
{
    QAction *a = QMenu::exec(pos, action);
    if (a == nullptr) {
        a = _current_action;
    }
    _current_action = nullptr;

    return a;
}

QFont zcHtmlMenu::drawBackground(QPainter &p, const QRect &, bool hovered, internal_zcHtmlMenuItem *label)
{
    QStyleOptionMenuItem opt;
    QAction *action = _actions[label];
    initStyleOption(&opt, action);

    if (hovered) {
        opt.state.setFlag(QStyle::State_Selected);
    }

    style()->drawControl(QStyle::CE_MenuItem, &opt, &p, this);

    return opt.font;
}

void zcHtmlMenu::setActiveHtmlItem(internal_zcHtmlMenuItem *item)
{
    if (item == nullptr) {
        setActiveAction(nullptr);
    } else {
        if (_actions.contains(item)) {
            QAction *a = _actions[item];
            setActiveAction(a);
        } else {
            setActiveAction(nullptr);
        }
    }
}

bool zcHtmlMenu::isActiveHtmlItem(internal_zcHtmlMenuItem *item)
{
    if (item == nullptr) {
        return false;
    } else {
        if (_actions.contains(item)) {
            QAction *a = _actions[item];
            QAction *active = activeAction();
            return a == active;
        } else {
            return false;
        }
    }
}


void zcHtmlMenu::htmlActionTriggered()
{
    QAction *current = qobject_cast<QAction *>(sender());
    _current_action = current;
}

void zcHtmlMenu::htmlActionChanged()
{
    QAction *current = qobject_cast<QAction *>(sender());
    if (_items.contains(current)) {
        internal_zcHtmlMenuItem *item = _items[current];
        item->setHtml(current->text());
        item->setIcon(current->icon());
    }
}

int zcHtmlMenu::version_major()
{
    return zcHtmlMenu_VERSION_MAJOR;
}

int zcHtmlMenu::version_minor()
{
    return zcHtmlMenu_VERSION_MINOR;
}

QString zcHtmlMenu::version()
{
    return QString("%1.%2").arg(QString::number(zcHtmlMenu_VERSION_MAJOR),
                                QString::number(zcHtmlMenu_VERSION_MINOR)
                                );
}
