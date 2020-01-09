#ifndef ZCCOLORPICKERACTION_H
#define ZCCOLORPICKERACTION_H

#include <QWidget>
#include <QAction>
#include <QWidgetAction>

#include "zccolor.h"

#ifdef Q_QDOC
class zcColorPickerAction : public QWidgetAction
#else
class LIBQTEXTENSIONS_EXPORT zcColorPickerAction : public QWidgetAction
#endif
{
    Q_OBJECT
public:
    explicit zcColorPickerAction(QWidget *parent = nullptr);
    explicit zcColorPickerAction(bool withDlg, QWidget *parent = nullptr);

public:
    QColor colorChoosen();
    bool    isColorChoosen();
};

#endif // ZCCOLORPICKERACTION_H
