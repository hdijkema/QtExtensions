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

#include <QHash>

#include "zcdebug.h"
#include "zcatexit.h"

static QHash<void *, const char *> _allocations;
static QHash<void *, const char *> _deallocated;

static void cleanup()
{
    if (!_allocations.isEmpty()) {

        LINE_WARNING << "Still" << _allocations.size() << "allocations left";

        QHash<const char *, int> functions;
        QHash<void *, const char *>::iterator it = _allocations.begin();
        while(it != _allocations.end()) {
            const char *f = it.value();
            if (functions.contains(f)) {
                int c = functions[f];
                c += 1;
                functions[f] = c;
            } else {
                functions[f] = 1;
            }
            it++;
        }

        foreach(const char *func, functions.keys()) {
            LINE_WARNING << func << ": " << functions[func] << " allocations";
        }
    }
}

static void init()
{
    static bool _init = true;
    if (_init) {
        zcAtExit::atexitLast("zcdebug - cleanup", cleanup);
        _init = false;
    }
}

LIBQTEXTENSIONS_EXPORT void zc_dbg_mem_crt(const char *func, void *pointer)
{
    init();
    if (_allocations.contains(pointer)) {
        LINE_CRITICAL << func << "Memory location in use:" << pointer;
    } else {
        _allocations.insert(pointer, func);
    }
}

LIBQTEXTENSIONS_EXPORT void zc_dbg_mem_dlt(const char *func, void *pointer)
{
    init();
    if (_allocations.contains(pointer)) {
        const char *f = _allocations[pointer];
        if (strcmp(func, f) != 0) {
            LINE_CRITICAL << func << "deleting previous allocation for:" << f << " pointer = " << pointer;
        } else {
            _allocations.remove(pointer);
            _deallocated.insert(pointer, func);
        }
    } else {
        if (_deallocated.contains(pointer)) {
            const char *f = _deallocated[pointer];
            if (strcmp(func, f) == 0) {
                LINE_CRITICAL << func << "Suspect deallocation for the second time:" << pointer;
            }
        } else {
            LINE_CRITICAL << func << "Suspect deallocation of non allocated pointer:" << pointer;
        }
    }
}
