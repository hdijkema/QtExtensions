#include "qtextensionswindow.h"
#include "ui_qtextensionswindow.h"

QtExtensionsWindow::QtExtensionsWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::QtExtensionsWindow)
{
    ui->setupUi(this);

    connect(ui->fr_colorpicker, &zcColorPicker::colorChoosen, this, &QtExtensionsWindow::setColorChoosen);
}

QtExtensionsWindow::~QtExtensionsWindow()
{
    delete ui;
}

void QtExtensionsWindow::setColorChoosen(const zcColor &c)
{
    ui->lb_color->setText(QString("<span style=\"background: %1;\">Color %2 choosen</span>").arg(
                              c.toHTML(), c.toHTML()
                              )
                          );
}

