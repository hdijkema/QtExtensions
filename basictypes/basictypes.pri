
SOURCES += $$PWD/zcfont.cpp \
    $$PWD/zcbezier.cpp \
    $$PWD/zccolor.cpp \
    $$PWD/zcprefsprovider.cpp \
    $$PWD/zcpresspoint.cpp

HEADERS += $$PWD/zcfont.h \
    $$PWD/zcbezier.h \
    $$PWD/zccolor.h \
    $$PWD/zclib_defaults.h \
    $$PWD/zcprefsprovider.h \
    $$PWD/zcpresspoint.h


contains(TEMPLATE, lib) {
  INCLUDEPATH += basictypes
} else {
  INCLUDEPATH += ../basictypes
}

headers.files += $$PWD/zcfont.h \
    $$PWD/zcbezier.h \
    $$PWD/zccolor.h \
    $$PWD/zclib_defaults.h \
    $$PWD/zcpresspoint.h \
    $$PWD/zcprefsprovider.h

