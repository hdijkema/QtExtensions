
SOURCES += $$PWD/zchtmlmenu.cpp \
    $$PWD/zchtmlmenuitem.cpp \
    $$PWD/zchtmlmenuitemlabel.cpp

HEADERS += $$PWD/zchtmlmenu.h \
    $$PWD/zchtmlmenuitem.h \
    $$PWD/zchtmlmenuitemlabel.h


contains(TEMPLATE, lib) {
  INCLUDEPATH += zchtmlmenu
} else {
  INCLUDEPATH += ../zchtmlmenu
}

headers.files += $$PWD/zchtmlmenu.h

