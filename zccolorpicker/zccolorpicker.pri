
SOURCES += $$PWD/zccolorpicker.cpp \
    $$PWD/internal_colorpickerbutton.cpp \
    $$PWD/zccolorpickeraction.cpp

HEADERS += $$PWD/zccolorpicker.h \
    $$PWD/internal_colorpickerbutton.h \
    $$PWD/zccolorpickeraction.h

contains(TEMPLATE, lib) {
  INCLUDEPATH += zccolorpicker
} else {
  INCLUDEPATH += ../zccolorpicker
}

headers.files += $$PWD/zccolorpicker.h, $$PWD/zccolorpickeraction.h

