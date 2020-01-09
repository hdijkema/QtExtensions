#ifndef INTERNAL_COLORPICKERBUTTON_H
#define INTERNAL_COLORPICKERBUTTON_H

#include <QWidget>
//#include <QToolButton>
#include <QLabel>
#include "zccolor.h"

class internal_ColorPickerButton : public QLabel
{
    Q_OBJECT
public:
    explicit internal_ColorPickerButton(const zcColor &color, const QString &tooltip, QWidget *parent = nullptr);
    explicit internal_ColorPickerButton(const QString &text, QWidget *parent = nullptr);


    // QWidget interface
protected:
    void mouseReleaseEvent(QMouseEvent *event);

public:
    void setIcon(const QIcon &icon);

signals:
    void clicked();
};

#endif // INTERNAL_COLORPICKERBUTTON_H
