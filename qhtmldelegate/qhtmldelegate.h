#ifndef HTMLDELAGATE_H
#define HTMLDELAGATE_H
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
    along with ZCLibs. If not, see <https://www.gnu.org/licenses/lgpl.html>.

EL***/

#include <QObject>
#include <QStyledItemDelegate>
#include <QTextDocument>

#include "libqtextensions_global.h"


class LIBQTEXTENSIONS_EXPORT QHtmlDelegate : public QStyledItemDelegate
{
    Q_OBJECT
private:
    qreal                 _zoomFactor;
    mutable QTextDocument _doc;
public:
    QHtmlDelegate(QObject *parent = nullptr);
    void setZoomFactor(qreal factor);
protected:
    void paint ( QPainter * painter, const QStyleOptionViewItem & option, const QModelIndex & index ) const;
    QSize sizeHint ( const QStyleOptionViewItem & option, const QModelIndex & index ) const;
};


#endif // HTMLDELAGATE_H
