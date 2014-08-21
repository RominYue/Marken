#-------------------------------------------------
#
# Project created by QtCreator 2014-08-21T09:11:35
#
#-------------------------------------------------

QT       += core gui

CONFIG += c++11
QMAKE_CXXFLAGS += -std=c++0x

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Marken
TEMPLATE = app

TRANSLATIONS += lang/Lang_CH.ts

INCLUDEPATH += "./include"

SOURCES += src/main.cpp\
    src/marken.cpp \
    src/editor.cpp \
    src/previewer.cpp \
    src/markdownhighlighter.cpp \
    src/preferenceeditor.cpp \
    src/setting.cpp \
    src/settingeditor.cpp \
    src/colorschemenode.cpp \
    src/colorscheme.cpp

HEADERS  += include/marken.h \
    include/editor.h \
    include/previewer.h \
    include/markdownhighlighter.h \
    include/preferenceeditor.h \
    include/setting.h \
    include/settingeditor.h \
    include/colorschemenode.h \
    include/colorscheme.h

FORMS    += form/marken.ui \
    form/editor.ui \
    form/previewer.ui \
    form/preferenceeditor.ui
