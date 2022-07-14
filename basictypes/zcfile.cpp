/**

    This file is part of QtExtensions (https://github.com/hdijkema/QtExtensions).

    (c) Hans Dijkema 2020

    QtExtensions is free software: you can redistribute it and/or modify
    it under the terms of the GNU Lesser General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    Qtextensions is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU Lesser General Public License
    along with QtExtensions. If not, see <https://www.gnu.org/licenses/lgpl.html>.

**/

#include "zcdebug.h"
#include "zcfile.h"
#include "zcdir.h"
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <QRegularExpression>

#if defined(MSDOS) || defined(OS2) || defined(WIN32) || defined(__CYGWIN__)
#  include <fcntl.h>
#  include <io.h>
#  define SET_BINARY_MODE(file) setmode(fileno(file), O_BINARY)
#else
#  define SET_BINARY_MODE(file)
#endif

#define CHUNK 16384

static QString removePrefixSlash(QString s)
{
    while (s.startsWith("/") || s.startsWith("\\")) {
        s = s.mid(1);
    }
    return s;
}

zcFile::zcFile()
{
}

zcFile::zcFile(const QDir &dir, const QString &filename) :
    QFile(dir.absoluteFilePath(removePrefixSlash(filename)))
{
}

zcFile::zcFile(const QString &filename)
    : QFile(filename)
{
}

zcFile::zcFile(const QFile &f) :
    QFile(f.fileName())
{
}

zcFile::zcFile(const zcFile &f)
    : QFile(f.fileName())
{
}

QString zcFile::canonical(QString fn)
{
#ifdef QT6
    QRegularExpression re("[^a-zA-Z0-9-_]");
#else
    QRegExp re("[^a-zA-Z0-9-_]");
#endif
    fn.replace(re, "_");
    return fn;
}

void zcFile::operator =(const zcFile &other)
{
    this->setFileName(other.fileName());
}

zcFile zcFile::findBasename(const QString &name, QDir basedir, bool recursive, bool &found)
{
#ifdef Q_OS_WIN
    auto eq = [](QString f1, QString f2) {
        return f1.compare(f2, Qt::CaseInsensitive) == 0;
    };
#else
    #ifdef Q_OS_MAC
        auto eq = [](QString f1, QString f2) {
            return f1.compare(f2, Qt::CaseInsensitive) == 0;
        };
    #else // Linux
    auto eq = [](QString f1, QString f2) {
        return f1 == f2;
    };
    #endif
#endif

    QStringList entries = basedir.entryList(QDir::Executable|QDir::Files);
    int i, N;
    for(i = 0, N = entries.size();i < N && !eq(entries[i], name); i++);

    if (i != N) {
        found = true;
        zcFile f(basedir, name);
        return f;
    } else if (recursive) {
        entries = basedir.entryList(QDir::AllDirs|QDir::NoDotAndDotDot);
        for(i = 0, N = entries.size(); i < N; i++) {
            zcDir d(basedir, entries[i]);
            found = false;
            zcFile f = findBasename(name, d, recursive, found);
            if (found) {
                return f;
            }
        }
        found = false;
        zcFile f;
        return f;
    } else {
        found = false;
        zcFile f;
        return f;
    }
}

#define BUFSIZE 16384
#define MAX_BUFSIZE (5 * 16384)
bool zcFile::copy(zcFile to_file, std::function<void (int)> f_progress_perc)
{
    f_progress_perc(0);
    if (size() <= MAX_BUFSIZE) {
        bool b = QFile::copy(to_file.absolutePath());
        if (b) { f_progress_perc(100); }
        return b;
    }
    else {
        char buf[BUFSIZE];
        if (QFile::isOpen()) { QFile::close(); }
        if (to_file.isOpen()) { to_file.close(); }
        if (QFile::open(QIODevice::ReadOnly)) {
            qint64 bytes = QFile::size();
            qint64 written = 0;
            if (to_file.open(QIODevice::WriteOnly)) {
                qint64 bytes_read = QFile::read(buf, BUFSIZE);
                int perc = -1;
                while (bytes_read == BUFSIZE) {
                    int e = to_file.write(buf, bytes_read);
                    if (e >= 0) {
                        written += bytes_read;
                        int p = written / bytes;
                        if (p != perc) { perc = p; f_progress_perc(perc); }
                        bytes_read = QFile::read(buf, BUFSIZE);
                    } else {
                        bytes_read = -1;
                    }
                }
                if (bytes_read == -1) {
                    QFile::close();
                    to_file.close();
                    to_file.remove();
                    return false;
                } else {
                    int e = to_file.write(buf, bytes_read);
                    if (e < 0) {
                        QFile::close();
                        to_file.close();
                        to_file.remove();
                        return false;
                    } else {
                        f_progress_perc(100);
                        QFile::close();
                        to_file.close();

                        if (!to_file.setPermissions(QFile::permissions())) {
                            LINE_WARNING << "Cannot set permissions on file copied to (" << to_file
                                         << "), from source file (" << *this << ")";
                            LINE_WARNING << "Permissable error, function still returns true";
                        }
                        return true;
                    }
                }
            } else {
                QFile::close();
            }
        }
        return false;
    }
}

bool zcFile::copy(const QString &to_file)
{
    return QFile::copy(to_file);
}

QIODevice *zcFile::device()
{
    return this;
}

QString zcFile::basename() const
{
    QFileInfo fi(*this);
    return fi.fileName();
}

zcDir zcFile::basedir() const
{
    QFileInfo fi(*this);
    zcDir d(fi.absolutePath());
    return d;
}

QString zcFile::ext() const
{
    QFileInfo i(*this);
    return i.suffix();
}

QString zcFile::basenameNoExt() const
{
    QString n(basename());
    int idx = n.lastIndexOf(".");
    if (idx >= 0) {
        n = n.left(idx);
    }
    return n;
}

bool zcFile::copyWrt(QString toFileName)
{
    if (QFile::copy(toFileName)) {
        zcFile f(toFileName);
        return f.setPermissions(QFile::WriteOwner|QFile::WriteGroup|QFile::ReadOwner|QFile::ReadGroup);
    } else {
        return false;
    }
}

QString zcFile::absolutePath() const
{
    QFileInfo fi(*this);
    return fi.absoluteFilePath();
}

LIBQTEXTENSIONS_EXPORT QDebug operator <<(QDebug out, const zcFile & f)
{
    out << "zcFile::" << f.absolutePath();
    return out;
}
