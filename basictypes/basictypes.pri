
SOURCES += $$PWD/zcfont.cpp \
    $$PWD/zcatexit.cpp \
    $$PWD/zcbezier.cpp \
    $$PWD/zccolor.cpp \
    $$PWD/zcdebug.cpp \
    $$PWD/zcdir.cpp \
    $$PWD/zcfile.cpp \
    $$PWD/zcprefsprovider.cpp \
    $$PWD/zcpresspoint.cpp

HEADERS += $$PWD/zcfont.h \
    $$PWD/zcatexit.h \
    $$PWD/zcbezier.h \
    $$PWD/zccolor.h \
    $$PWD/zcdebug.h \
    $$PWD/zcdir.h \
    $$PWD/zcfile.h \
    $$PWD/zclib_defaults.h \
    $$PWD/zcprefsprovider.h \
    $$PWD/zcpresspoint.h


contains(TEMPLATE, lib) {
  INCLUDEPATH += basictypes
} else {
  INCLUDEPATH += ../basictypes
}

headers.files += $$PWD/zcfont.h \
    $$PWD/zcatexit.h \
    $$PWD/zcbezier.h \
    $$PWD/zccolor.h \
    $$PWD/zcdebug.h \
    $$PWD/zcdir.h \
    $$PWD/zcfile.h \
    $$PWD/zclib_defaults.h \
    $$PWD/zcprefsprovider.h \
    $$PWD/zcpresspoint.h

