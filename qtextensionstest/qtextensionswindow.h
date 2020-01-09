#ifndef QTEXTENSIONSWINDOW_H
#define QTEXTENSIONSWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class QtExtensionsWindow; }
QT_END_NAMESPACE

#include "zccolor.h"

class QtExtensionsWindow : public QMainWindow
{
    Q_OBJECT

public:
    QtExtensionsWindow(QWidget *parent = nullptr);
    ~QtExtensionsWindow();

private:
    Ui::QtExtensionsWindow *ui;

private slots:
    void setColorChoosen(const zcColor &c);
};
#endif // QTEXTENSIONSWINDOW_H
