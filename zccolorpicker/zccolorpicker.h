#ifndef ZCCOLORPICKER_H
#define ZCCOLORPICKER_H
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
#include <QFrame>
#include <QAction>
#include <QColor>
#include <QMenu>

#include "zcprefsprovider.h"
#include "zccolorpickeraction.h"

class zcColorPicker : public QFrame
{
    Q_OBJECT
private:
    zcColorPickerAction  *_my_action;
    QString               _color_choosen;
    bool                  _choosen;
    zcPrefsProvider       _prefs;

public:
    explicit zcColorPicker(bool withColorDlg, QWidget *parent = nullptr);

public:
    static zcColorPickerAction *addColorPickerAction(QMenu *menu, const QString &label, bool withColDlg);
    void setAction(zcColorPickerAction *action);

public:
    QString choosenColorHTML();
    QColor  choosenColor();
    bool    isColorChoosen();
    void    setIsColorChoosen(bool y);

public:
    void setPrefFuncs(zcPrefsProvider::Funcs funcs);

private slots:
    void colorChoosenSlot();
    void colorDialog();

signals:
    void colorChoosen(const zcColor &color);

private:
    void internalColorChoosen(const zcColor &c);

    // QWidget interface
protected:
    void mouseReleaseEvent(QMouseEvent *event);
};

#endif // ZCCOLORPICKER_H
