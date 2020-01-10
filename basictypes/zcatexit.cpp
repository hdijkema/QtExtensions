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

#include "zcatexit.h"
#include "zcdebug.h"

#include <QCoreApplication>

static zcAtExit *_at_exit = nullptr;

typedef struct _FS_ {
    struct _FS_ *next;
    const char  *func;
    zcAtExitFunc f;
    bool         report;
    bool         report_after;
} funcs_t;

static funcs_t *first = nullptr;

void runLastAtExits()
{
    funcs_t *e = first;
    while(e != nullptr) {
        bool report = e->report;
        bool report_after = e->report_after;

        if (report) LINE_DEBUG << e->func << " - start";

        e->f();

        if (report_after) LINE_DEBUG << e->func << " - done";

        funcs_t *d = e;
        e = e->next;
        free(d);
    }
}

zcAtExit::zcAtExit(QCoreApplication *app) : QObject(app)
{
    if (_at_exit != nullptr) {
        LINE_CRITICAL << "This object can only be instantiated once";
        exit(1);
    } else {
        _at_exit = this;
        _app = app;
        connect(app, &QCoreApplication::aboutToQuit, this, &zcAtExit::runAtExits);
    }
}

zcAtExit::~zcAtExit()
{
    LINE_DEBUG;
    disconnect(_app, &QCoreApplication::aboutToQuit, this, &zcAtExit::runAtExits);
    _at_exit = nullptr;

}

void zcAtExit::atexit(const char *func, zcAtExitFunc f, bool report_before, bool report_after)
{
    if (_at_exit == nullptr) {
        LINE_CRITICAL << "Instantiate zcAtExit() first!";
        exit(1);
    } else {
        _at_exit->_handlers.append(f);
        _at_exit->_funcs.append(func);
        _at_exit->_report.append(report_before);
        _at_exit->_report_after.append(report_after);
    }
}

void zcAtExit::atexitLast(const char *func, zcAtExitFunc f, bool report_before, bool report_after)
{
    if (_at_exit == nullptr) {
        LINE_CRITICAL << "Instantiate zcAtExit() first!";
        exit(1);
    } else {
        if (first == nullptr) { ::atexit(runLastAtExits); }
        funcs_t *e = reinterpret_cast<funcs_t *>(malloc(sizeof(funcs_t)));
        e->next = first;
        e->func = func;
        e->f = f;
        e->report = report_before;
        e->report_after = report_after;
        first = e;
    }
}

void zcAtExit::runAtExits()
{
    LINE_DEBUG;

    int i, N;
    for(i = 0, N = _handlers.size(); i < N; i++) {
        zcAtExitFunc f = _handlers[i];
        const char *func = _funcs[i];
        bool report = _report[i];
        bool report_after = _report_after[i];

        if (report) LINE_DEBUG << "At Exit:" << func;

        f();

        if (report_after) LINE_DEBUG << "At Exit - end:" << func;
    }
    _handlers.clear();
}

