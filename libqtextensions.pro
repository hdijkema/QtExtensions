# Install prefix
mac: PREFIX=/Users/hans/devel/libraries/osx
win32: PREFIX=c:/devel/libraries/win64

# Sources are here
win32:SRC_PREFIX=../qtextensions
unix:SRC_PREFIX=../qtextensions

QT += core gui widgets

TEMPLATE = lib
DEFINES += LIBQTEXTENSIONS_LIBRARY

CONFIG += c++11

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

mac: QMAKE_MACOSX_DEPLOYMENT_TARGET = 10.8

MYQMAKE=$$[QT_INSTALL_BINS]/qmake

SOURCES += \
    libqtextensions.cpp

HEADERS += \
    libqtextensions_global.h \
    libqtextensions.h

TRANSLATIONS += \
    libqtextensions_nl_NL.ts

# Default rules for deployment.

PREFIX=$$PREFIX
SRC_PREFIX=$$SRC_PREFIX

LIB_TARGET=lib
CONFIG(debug, release|debug) {
LIB_TARGET=libd
}

target.path = $$PREFIX/$$LIB_TARGET

INSTALLS += target

#### Headers to install
headers.path = $$PREFIX/include/qtextensions
headers.files = libqtextensions.h libqtextensions_global.h

#### Documentation
win32: QTEXTENSIONS_VERSION_MAJOR = $$system(findstr /C:QTEXTENSIONS_VERSION_MAJOR libqtextensions.h)
mac: QTEXTENSIONS_VERSION_MAJOR=$$system(grep QTEXTENSIONS_VERSION_MAJOR libqtextensions.h)
linux: QTEXTENSIONS_VERSION_MAJOR=$$system(grep QTEXTENSIONS_VERSION_MAJOR libqtextensions.h)

QTEXTENSIONS_VERSION_MAJOR = $$replace(QTEXTENSIONS_VERSION_MAJOR, define, )
QTEXTENSIONS_VERSION_MAJOR = $$replace(QTEXTENSIONS_VERSION_MAJOR, QTEXTENSIONS_VERSION_MAJOR, )
QTEXTENSIONS_VERSION_MAJOR = $$replace(QTEXTENSIONS_VERSION_MAJOR, $$LITERAL_HASH, )
QTEXTENSIONS_VERSION_MAJOR = $$QTEXTENSIONS_VERSION_MAJOR

win32: QTEXTENSIONS_VERSION_MINOR = $$system(findstr /C:QTEXTENSIONS_VERSION_MINOR libqtextensions.h)
mac: QTEXTENSIONS_VERSION_MINOR=$$system(grep QTEXTENSIONS_VERSION_MINOR libqtextensions.h)
linux: QTEXTENSIONS_VERSION_MINOR=$$system(grep QTEXTENSIONS_VERSION_MINOR libqtextensions.h)

QTEXTENSIONS_VERSION_MINOR = $$replace(QTEXTENSIONS_VERSION_MINOR, define, )
QTEXTENSIONS_VERSION_MINOR = $$replace(QTEXTENSIONS_VERSION_MINOR, QTEXTENSIONS_VERSION_MINOR, )
QTEXTENSIONS_VERSION_MINOR = $$replace(QTEXTENSIONS_VERSION_MINOR, $$LITERAL_HASH, )
QTEXTENSIONS_VERSION_MINOR = $$QTEXTENSIONS_VERSION_MINOR

message(version: $$QTEXTENSIONS_VERSION_MAJOR $$QTEXTENSIONS_VERSION_MINOR)


documentation.path = $$PREFIX/doc/qtextensions
win32: documentation.files = doc/*
win32: documentation.extra = $$shell_path($$SRC_PREFIX\qtextensions_mkdoc.bat) \
          $$QTEXTENSIONS_VERSION_MAJOR $$QTEXTENSIONS_VERSION_MINOR \
          $$shell_path($$MYQMAKE) $$shell_path($$SRC_PREFIX) $$shell_path($$PREFIX/doc/qtextensions)

#### Sources
include(basictypes/basictypes.pri)
include(zchtmlmenu/zchtmlmenu.pri)
include(zchtmldelegate/zchtmldelegate.pri)
include(zccoloricon/zccoloricon.pri)
include(zccolorpicker/zccolorpicker.pri);

INSTALLS += headers
INSTALLS += documentation

DISTFILES += \
    libqtextensions.qdocconf \
    qtextensions_mkdoc.bat


