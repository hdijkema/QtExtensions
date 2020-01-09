
SOURCES += $$PWD/zchtmldelegate.cpp

HEADERS += $$PWD/zchtmldelegate.h

contains(TEMPLATE, lib) {
  INCLUDEPATH += zchtmldelegate
} else {
  INCLUDEPATH += ../zchtmldelegate
}

headers.files += $$PWD/zchtmldelegate.h
