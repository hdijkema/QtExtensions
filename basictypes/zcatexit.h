#ifndef ZCATEXIT_H
#define ZCATEXIT_H

/**

    This file is part of QtExtensions (https://github.com/hdijkema/QtExtensions).

    (c) Hans Dijkema 2020

    QtExtensions is free software: you can redistribute it and/or modify
    it under the terms of the GNU Lesser General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    Foobar is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU Lesser General Public License
    along with QtExtensions. If not, see <https://www.gnu.org/licenses/lgpl.html>.

**/

#include "libqtextensions_global.h"

#include <QObject>

class QCoreApplication;

typedef void (*zcAtExitFunc)(void);

#ifdef Q_QDOC
class zcAtExit : public QObject
#else
class LIBQTEXTENSIONS_EXPORT zcAtExit : public QObject
#endif
{
    Q_OBJECT
private:
    QCoreApplication   *_app;
    QList<zcAtExitFunc> _handlers;
    QList<const char *> _funcs;
    QList<bool>         _report;
    QList<bool>         _report_after;

public:
    explicit zcAtExit(QCoreApplication *app);
    ~zcAtExit();

public:
    static void atexit(const char *func, zcAtExitFunc f, bool report_before = true, bool report_after = true);
    static void atexitLast(const char *func, zcAtExitFunc f, bool report_before = true, bool report_after = true);

public slots:
    void runAtExits();
};

#endif // ZCATEXIT_H
