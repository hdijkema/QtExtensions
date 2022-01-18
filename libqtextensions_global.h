#ifndef LIBQTEXTENSIONS_GLOBAL_H
#define LIBQTEXTENSIONS_GLOBAL_H
/**

    This file is part of QtExtensions (https://github.com/hdijkema/QtExtensions).

    (c) Hans Dijkema 2020

    QtExtensions is free software: you can redistribute it and/or modify
    it under the terms of the GNU Lesser General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    QtExtensions is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU Lesser General Public License
    along with QtExtensions. If not, see <https://www.gnu.org/licenses/lgpl.html>.

**/

#include <QtCore/qglobal.h>

#if defined(QTEXTENSIONSTEST)
#  define LIBQTEXTENSIONS_EXPORT
#else
#  if defined(LIBQTEXTENSIONS_LIBRARY)
#    define LIBQTEXTENSIONS_EXPORT Q_DECL_EXPORT
#  else
#    define LIBQTEXTENSIONS_EXPORT Q_DECL_IMPORT
#  endif
#endif

#ifndef QT6
#  if (QT_VERSION >= QT_VERSION_CHECK(6, 0, 0))
#    define QT6
#  endif
#endif

#endif // LIBQTEXTENSIONS_GLOBAL_H
