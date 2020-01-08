#ifndef INTERNAL_QHTMLMENUITEMLABEL_H
#define INTERNAL_QHTMLMENUITEMLABEL_H

#include <QWidget>
#include <QLabel>

class internal_QHtmlMenuItemLabel : public QLabel
{
    Q_OBJECT
public:
    explicit internal_QHtmlMenuItemLabel(QWidget *parent = nullptr);

    // QWidget interface
protected:
    void mouseReleaseEvent(QMouseEvent *event);
};

#endif // QHTMLMENUITEMLABEL_H
