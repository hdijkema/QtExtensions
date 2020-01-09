#include "qtextensionswindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QtExtensionsWindow w;
    w.show();
    return a.exec();
}
