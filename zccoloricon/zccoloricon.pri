
SOURCES += $$PWD/zccoloricon.cpp

HEADERS += $$PWD/zccoloricon.h

contains(TEMPLATE, lib) {
  INCLUDEPATH += zccoloricon
} else {
  INCLUDEPATH += ../zccoloricon
}

headers.files += $$PWD/zccoloricon.h

