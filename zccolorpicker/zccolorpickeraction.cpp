#include "zccolorpickeraction.h"
#include "zccolorpicker.h"

zcColorPickerAction::zcColorPickerAction(QWidget *parent)
    : zcColorPickerAction(true, parent)
{
}

zcColorPickerAction::zcColorPickerAction(bool withDlg, QWidget *parent)
    : QWidgetAction(parent)
{
    zcColorPicker *picker = new zcColorPicker(withDlg);
    picker->setAction(this);
    this->setDefaultWidget(picker);

    //connect(action, &QAction::triggered, menu, &QMenu::hide);
    //return action;
}

QColor zcColorPickerAction::colorChoosen()
{
    zcColorPicker *picker = qobject_cast<zcColorPicker *>(this->defaultWidget());
    return picker->choosenColor();
}

bool zcColorPickerAction::isColorChoosen()
{
    zcColorPicker *picker = qobject_cast<zcColorPicker *>(this->defaultWidget());
    return picker->isColorChoosen();
}
