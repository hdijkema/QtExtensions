#include "internal_colorpickerbutton.h"

#include <QMouseEvent>
#include <QIcon>
#include "zccoloricon.h"

internal_ColorPickerButton::internal_ColorPickerButton(const zcColor &color, const QString &tooltip, QWidget *parent)
    : QLabel(parent)
{
    internal_ColorPickerButton *btn = this;
    btn->setIcon(zcColorIcon(color, true));
    QString vcol = color.toHTML();
    btn->setProperty("kleur", vcol);
    btn->setToolTip(tooltip);
    QString linecol = zcColor(color.darker()).toHTML();
    btn->setStyleSheet(QString("QLabel { border:none;background-color:%1;margin:2px;padding:0; } "
                               "QLabel:hover { border:1px solid %2; }").arg(
                           vcol, linecol
                           )
                       );

}

internal_ColorPickerButton::internal_ColorPickerButton(const QString &text, QWidget *parent)
    : QLabel(text, parent)
{
    QColor c = Qt::black;
    QString linecol = zcColor(c).toHTML();
    setStyleSheet(QString("QLabel { border:none;margin:2px;padding:0; } "
                                   "QLabel:hover { border:1px solid %1; }").arg(
                               linecol
                               )
                           );
}

void internal_ColorPickerButton::mouseReleaseEvent(QMouseEvent *event)
{
    //QToolButton::mouseReleaseEvent(event);
    emit clicked();
    event->ignore();
}

void internal_ColorPickerButton::setIcon(const QIcon &icon)
{
    setPixmap(icon.pixmap(QSize(16, 16)));
}
