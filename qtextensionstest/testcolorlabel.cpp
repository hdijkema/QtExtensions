#include "testcolorlabel.h"
#include "zchtmlmenu.h"
#include "zccolorpicker.h"

TestColorLabel::TestColorLabel(QWidget *parent) : QLabel(parent)
{

}

void TestColorLabel::contextMenuEvent(QContextMenuEvent *)
{
    zcHtmlMenu *menu = new zcHtmlMenu("oke", this);
    QAction *a1 = menu->addHtmlAction("<b>Don't</b> choose a <i>color</i>.");
    QAction *a3 = menu->addHtmlAction("HA<b><i>L</i>L</b>O!");

    zcColorPickerAction *a2 = zcColorPicker::addColorPickerAction(menu, "Change color", true);
    connect(a2, &QAction::triggered, this, &TestColorLabel::setTextColor);

    QAction *a = menu->exec(QCursor::pos());

    if (a1 == a) {
        setText("No color choosen");
    } else if (a2 == a) {
        QString txt = text();
        txt += " - by menu!";
        setText(txt);
    } else if (a3 == a) {
        setText("HALLO!!!");
    }

    menu->deleteLater();
}

void TestColorLabel::setTextColor()
{
    zcColorPickerAction *a = qobject_cast<zcColorPickerAction *>(sender());
    if (a != nullptr) {
        zcColor c(a->colorChoosen());
        setText(QString("<span style=\"background: %1;\">Color choosen by context menu</span>").arg(c.toHTML()));
    } else {
        setText("a == nullptr!");
    }
}
