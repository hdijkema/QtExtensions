#include "libqtextensions.h"

/*!
 * \page Qt Extensions
 *
 * QtExtensions provides a library with extensions to the Qt Widgetset.
 * The following classes are provided:
 *
 * \list
 * \li libqtextensions - provided classes:
 *   \list
 *   \li QHtmlMenu
 *   \li QHtmlDelegate
 *   \endlist
 * \endlist
 */

#include <QObject>

QString QtExtensions::version()
{
    QString ver(QObject::tr("QtExtensions version %1.%2").arg(
                    QString::number(QTEXTENSIONS_VERSION_MAJOR),
                    QString::number(QTEXTENSIONS_VERSION_MINOR)
                    )
                );
    return ver;
}

QString QtExtensions::license()
{
    return QString(QObject::tr("GNU Lesser General Public License version 3"));
}

QString QtExtensions::licenseShort()
{
    return QString("LGPLv3");
}

QString QtExtensions::author()
{
    return QString("(c) %1 Hans Dijkema").arg(QTEXTENSIONS_DEVEL_YEARS);
}
