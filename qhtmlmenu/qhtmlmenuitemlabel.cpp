#include "qhtmlmenuitemlabel.h"

#include <QMouseEvent>

internal_QHtmlMenuItemLabel::internal_QHtmlMenuItemLabel(QWidget *parent) : QLabel(parent)
{
}

void internal_QHtmlMenuItemLabel::mouseReleaseEvent(QMouseEvent *event)
{
    event->ignore();
}
