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

#include "zccolorpicker.h"
#include "zccolorpickeraction.h"
#include "internal_colorpickerbutton.h"

#include <QGridLayout>
#include <QLabel>
#include <QFrame>
#include <QToolButton>
#include <QVariant>
#include <QWidgetAction>
#include <QColorDialog>
#include <QPushButton>
#include <QMouseEvent>

#include "zccolor.h"
#include "zccoloricon.h"
#include "zccolorpicker.h"

zcColorPicker::zcColorPicker(bool withColorDlg, QWidget *parent)
    : QFrame(parent)
{
    QGridLayout *layout = new QGridLayout();
    layout->setContentsMargins(0, 0, 0, 0);
    layout->setSpacing(0);

    auto mkLine = [this]() {
        QFrame *line = new QFrame(this);line->setFrameShape(QFrame::HLine);line->setFrameShadow(QFrame::Sunken);
        return line;
    };

    auto add = [&](zcColor color, QString tooltip, int row, int col) {
        internal_ColorPickerButton *btn = new internal_ColorPickerButton(color, tooltip, this);
        layout->addWidget(btn, row, col);
        connect(btn, &internal_ColorPickerButton::clicked, this, &zcColorPicker::colorChoosenSlot);
    };

    QStringList standardRow = { "#ffffff",   "#ff00ff",     "#ff0000",    "#00ff00",   "#0000ff",   "#00ffff",   "#ffff00" };
    QStringList names       = { tr("Wit"),   tr("Magenta"), tr("Rood"),   tr("Groen"), tr("Blauw"), tr("Cyaan"), tr("Geel")};
    QStringList firstRow    = { "#808080",   "#2c73c1",     "#c76c18",    "#d2d22d",   "#5faf4f",   "#d30020",      "#8e4996" };
    QStringList fr_names    = { tr("Grijs"), tr("Blauw"),   tr("Oranje"), tr("Geel"),  tr("Groen"), tr("Rood"),  tr("Paars") };

    QList<int> factor;
    factor << 190 << 160 << 130 << -150 << -250;
    QStringList factor_str = { tr("80% lichter"), tr("60% lichter"), tr("30% lichter"),
                               tr("50% van het origineel"), tr("33% van het origineel")
                             };

    int NCOLS = standardRow.size();

    int row = 0;

    int i, N;
    for(i = 0, N = firstRow.size(); i < N; i++) {
        add(zcColor(firstRow[i]), fr_names[i], row, i);
    }

    row += 1;

    int j, M;
    for(j = 0, M = factor.size(); j < M; j++) {
        for(i = 0, N = firstRow.size(); i < N; i++) {
            zcColor c(firstRow[i]);
            int f = factor[j];
            if (f < 0) {
                zcColor cn(c.darker(-f));
                add(cn, factor_str[j], row + j, i);
            } else {
                zcColor cn(c.lighter(f));
                add(cn, factor_str[j], row + j, i);
            }
        }
    }

    row += factor.size();

    layout->addWidget(mkLine(), row, 0, 1, NCOLS);

    row += 1;
    QLabel *label = new QLabel(tr("<b>Standaard kleuren</b>"), this);
    layout->addWidget(label, row, 0, 1, NCOLS, Qt::AlignVCenter|Qt::AlignHCenter);

    row += 1;
    layout->addWidget(mkLine(), row, 0, 1, NCOLS);

    row += 1;
    for(i = 0, N = standardRow.size(); i < N; i++) {
        zcColor c(standardRow[i]);
        add(c, names[i], row, i);
    }

    row += 1;
    layout->addWidget(mkLine(), row, 0, 1, NCOLS);

    row += 1;
    if (withColorDlg) {
        /*
        QPushButton *btn = new QPushButton(tr("Meer kleuren..."), this);
        connect(btn, &QPushButton::clicked, this, &zcColorPicker::colorDialog);
        */
        internal_ColorPickerButton *btn = new internal_ColorPickerButton(tr("Meer kleuren..."), this);
        connect(btn, &internal_ColorPickerButton::clicked, this, &zcColorPicker::colorDialog);
        layout->addWidget(btn, row, 0, 1, NCOLS);
    }

    setLayout(layout);

    _choosen = false;
    _color_choosen = "#ffffff";
    _my_action = nullptr;
}

void zcColorPicker::internalColorChoosen(const zcColor &c, bool trigger)
{
    QString kleur = c.toHTML();
    _prefs.set("colorpicker.lastcolor", kleur);
    _color_choosen = kleur;
    _choosen = true;
    if (_my_action != nullptr) {
        _my_action->setProperty("color", kleur);
        if (trigger) _my_action->trigger();
    }
    emit colorChoosen(zcColor(_color_choosen));
}

void zcColorPicker::mouseReleaseEvent(QMouseEvent *event)
{
    event->ignore();
}

void zcColorPicker::colorChoosenSlot()
{
    internal_ColorPickerButton *btn = qobject_cast<internal_ColorPickerButton *>(sender());
    if (btn != nullptr) {
        QString kleur = btn->property("kleur").toString();
        zcColor c(kleur);
        internalColorChoosen(c, false);
    }
}

void zcColorPicker::colorDialog()
{
    QString lastColor = _prefs.get("colorpicker.lastcolor", QString("#ffffff"));
    zcColor lc(lastColor);

    QColorDialog *dlg = new QColorDialog(lc, this);
    if (dlg->exec() == QDialog::Accepted) {
        zcColor c(dlg->selectedColor());
        internalColorChoosen(c, true);
    }
    dlg->deleteLater();
}

void zcColorPicker::setAction(zcColorPickerAction *action)
{
    _my_action = action;
}

QString zcColorPicker::choosenColorHTML()
{
    return _color_choosen;
}

QColor zcColorPicker::choosenColor()
{
    return zcColor(_color_choosen);
}

void zcColorPicker::setIsColorChoosen(bool y)
{
    _choosen = y;
}

bool zcColorPicker::isColorChoosen()
{
    return _choosen;
}

void zcColorPicker::setPrefFuncs(zcPrefsProvider::Funcs funcs)
{
    _prefs.setFuncs(funcs);
}

zcColorPickerAction *zcColorPicker::addColorPickerAction(QMenu *menu, const QString &label, bool withColDlg)
{
    QMenu *submenu = menu->addMenu(label);
    zcColorPickerAction *action = new zcColorPickerAction(withColDlg, submenu);
    submenu->addAction(action);
    return action;
}


