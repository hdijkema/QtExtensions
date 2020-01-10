#include "qtextensionswindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
#ifdef Q_OS_WIN
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
#if QT_VERSION_MAJOR == 5 && QT_VERSION_MINOR >= 14
    QGuiApplication::setHighDpiScaleFactorRoundingPolicy(Qt::HighDpiScaleFactorRoundingPolicy::PassThrough);
#endif
#else
#ifdef Q_OS_LINUX // X11
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
#endif
#endif

    QApplication a(argc, argv);
    QtExtensionsWindow w;
    w.show();
    return a.exec();
}
