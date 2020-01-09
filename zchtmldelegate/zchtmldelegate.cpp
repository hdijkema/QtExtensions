/***BL

    This file is part of ZCLibs (https://github.com/hdijkema/zclibs).

    (c) Hans Dijkema 2016, 2017, 2018

    Foobar is free software: you can redistribute it and/or modify
    it under the terms of the GNU Lesser General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    Foobar is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU Lesser General Public License
    along with ZCLibs.  If not, see <https://www.gnu.org/licenses/lgpl.html>.

EL***/

#include <QApplication>
#include <QTextDocument>
#include <QAbstractTextDocumentLayout>
#include <QPainter>
#include <QStyleOptionViewItem>
#include <QModelIndex>
#include <QDebug>

#include "zchtmldelegate.h"
#include "zcfont.h"

zcHtmlDelegate::zcHtmlDelegate(QObject *parent)
    : QStyledItemDelegate(parent)
{
    _zoomFactor = 1.0;
}

void zcHtmlDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    painter->save();

    QStyleOptionViewItem optionV4 = option;
    initStyleOption(&optionV4, index);

    QStyle *style = optionV4.widget? optionV4.widget->style() : QApplication::style();

    QTextDocument doc;

    zcFont f(doc.defaultFont());
    doc.setDefaultFont(f.deriveScaled(_zoomFactor));
    doc.setHtml(optionV4.text);

    /// Painting item without text
    optionV4.text = QString();
    style->drawControl(QStyle::CE_ItemViewItem, &optionV4, painter);

    QAbstractTextDocumentLayout::PaintContext ctx;

    QRect textRect = style->subElementRect(QStyle::SE_ItemViewItemText, &optionV4);
    painter->translate(textRect.topLeft());
    painter->setClipRect(textRect.translated(-textRect.topLeft()));
    doc.documentLayout()->draw(painter, ctx);
    painter->restore();
}

QSize zcHtmlDelegate::sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    QStyleOptionViewItem optionV4 = option;
    initStyleOption(&optionV4, index);

    QTextDocument doc;

    zcFont f(doc.defaultFont());
    doc.setDefaultFont(f.deriveScaled(_zoomFactor));
    doc.setHtml(optionV4.text);
    return QSize(static_cast<int>(doc.idealWidth()), static_cast<int>(doc.size().height()));
}

void zcHtmlDelegate::setZoomFactor(qreal factor)
{
    _zoomFactor = factor;
    QModelIndex idx;
    emit sizeHintChanged(idx);
}
