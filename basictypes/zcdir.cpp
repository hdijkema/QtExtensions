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

#include "zcdir.h"
#include <QProcessEnvironment>
#ifndef ZC4CRYPT
#include <QDesktopServices>
#endif
#include <QUrl>
#include <QDebug>

zcDir::zcDir(const QDir &dir) : QDir(dir)
{
    _valid = true;
}

zcDir::zcDir(const zcDir &dir) : QDir(dir)
{
    _valid = dir.isValid();
}

zcDir::zcDir(const QString &path) : QDir(path)
{
    if (path == "") {
        _valid = false;
    } else {
        _valid = true;
    }
}

zcDir::zcDir(const QDir &dir, const QString &subdir) : QDir(dir.absoluteFilePath(subdir))
{
    _valid = true;
}

bool zcDir::mkpath()
{
    return super::mkpath(super::absolutePath());
}

bool zcDir::mkpath(const QString &dir)
{
    return super::mkpath(dir);
}

bool zcDir::isDir()
{
    QFileInfo f(super::absolutePath());
    return f.isDir();
}

bool zcDir::openInFileManager()
{
    QString pathIn = this->absolutePath();

    // Mac, Windows support folder or file.
#if defined(Q_OS_WIN)
    QStringList args;
    pathIn += "/.";
    args << QDir::toNativeSeparators(pathIn);
    QProcess::startDetached("explorer", args);
    return true;
#elif defined(Q_OS_MAC)
    //QStringList scriptArgs;
    //scriptArgs << QLatin1String("-e")
    //           << QString::fromLatin1("tell application \"Finder\" to reveal POSIX file \"%1\"")
    //                                 .arg(pathIn);
    //QProcess::execute(QLatin1String("/usr/bin/osascript"), scriptArgs);
    //scriptArgs.clear();
    //scriptArgs << QLatin1String("-e")
    //           << QLatin1String("tell application \"Finder\" to activate");
    //QProcess::execute("/usr/bin/osascript", scriptArgs);
    //return true;

    QString path = pathIn + "/.";
    QStringList args;
        args << "-e";
        args << "tell application \"Finder\"";
        args << "-e";
        args << "activate";
        args << "-e";
        args << "select POSIX file \"" + path + "\"";
        args << "-e";
        args << "end tell";
        QProcess::execute("/usr/bin/osascript", args);
    return true;
#else
#ifndef ZC4CRYPT
    return QDesktopServices::openUrl(QUrl::fromLocalFile(pathIn));
#else
    return false;
#endif
    /*
    // we cannot select a file here, because no file browser really supports it...
    const QFileInfo fileInfo(pathIn);
    const QString folder = fileInfo.absoluteFilePath();
    const QString app = Utils::UnixUtils::fileBrowser(Core::ICore::instance()->settings());
    QProcess browserProc;
    const QString browserArgs = Utils::UnixUtils::substituteFileBrowserParameters(app, folder);
    bool success = browserProc.startDetached(browserArgs);
    const QString error = QString::fromLocal8Bit(browserProc.readAllStandardError());
    success = success && error.isEmpty();
    return success;
    */
#endif
}

/*
#include <direct.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

bool zcDir::cdto()
{
    //return this->cd(this->absolutePath());
    QByteArray ba(this->absolutePath().toUtf8());
    int cd = _chdir(ba.data());
    return cd == 0;
}
*/

const QString zcDir::file(const QString &filename) const
{
    return this->absoluteFilePath(filename);
}


