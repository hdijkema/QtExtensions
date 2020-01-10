#ifndef ZCFILE_H
#define ZCFILE_H
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
#include <QFile>
#include <QDir>
#include <functional>
#include <QDebug>

class zcDir;

#ifdef Q_QDOC
class zcFile : public QFile
#else
class LIBQTEXTENSIONS_EXPORT zcFile : public QFile
#endif
{
public:
    zcFile();
    zcFile(const QDir &dir, const QString & filename);
    zcFile(const QString & filename);
    zcFile(const QFile & f);
    zcFile(const zcFile & f);

public:
    static QString canonical(QString fn);

public:
    operator QString() const { return this->fileName(); }

    /**
     * @brief basename - returns the complete filename with suffix.
     * @return
     */
    QString basename() const;

    /**
     * @brief basedir - returns the directory of the filename
     * @return
     */
    zcDir basedir() const;

    /**
     * @brief absolutePath - returns the complete path to the file, including the basename()
     * @return
     */
    QString absolutePath() const;

    /**
     * @brief ext - returns the last extension of the filename
     * @return
     */
    QString ext() const;

    /**
     * @brief basenameNoExt - returns basename() without ext() and the '.' before it.
     * @return
     */
    QString basenameNoExt() const;


    /**
     * @brief copyWrt - Copies the current file to toFileName and makes toFileName writable.
     * @param toFileName
     * @return
     */
    bool copyWrt(QString toFileName);

    void operator = (const zcFile & other);

    zcFile findBasename(const QString &name, QDir basedir, bool recursive, bool &found);

public:
    QIODevice *device();
};

LIBQTEXTENSIONS_EXPORT QDebug operator <<(QDebug out, const zcFile & c);

#endif // ZCFILE_H
