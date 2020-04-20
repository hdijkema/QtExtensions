#ifndef ZCDIR_H
#define ZCDIR_H
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
#include <QDir>
#include <functional>

#ifdef Q_QDOC
class zcDir : public QDir
#else
class LIBQTEXTENSIONS_EXPORT zcDir : public QDir
#endif
{
private:
    typedef QDir super;

private:
    bool _valid;

public:
    zcDir(const QDir & dir);
    zcDir(const zcDir & dir);
    zcDir(const QString & path = QString());
    zcDir(const QDir & dir, const QString & subdir);

public:
    /**
     * @brief The application can set this value to true or false.
     * Defaults to true.
     * @param v
     */
    void setValid(bool v)   { _valid = v; }
    bool isValid() const    { return _valid; }

public:
    /**
     * @brief Creates the current directory if it doesn't exist.
     * @return true on success.
     */
    bool mkpath();

    /**
     * @brief Creates the directory dir
     * @param dir
     * @return
     */
    bool mkpath(const QString &dir);


    /**
     * @brief True if the current zcDir points to a directory.
     * @return
     */
    bool isDir();
   //bool cdto();

public:
    const QString file(const QString &filename) const;

    /**
     * @brief openInFileManager - open deze directory in de file manager van het gegeven OS.
     * @return
     */
    bool openInFileManager();

public:
    /**
      * @brief maps function f for al files in this directory, recursively.
      * f is called with a full absolute path to the file to be processed.
      * @return returns true if all files have been processed.
      */
    bool mapRecurse(std::function<bool (QFile &, int count, int total)> f);
};

#endif // ZCDIR_H
