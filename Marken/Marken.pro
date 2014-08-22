#-------------------------------------------------
#
# Project created by QtCreator 2014-08-21T09:11:35
#
#-------------------------------------------------

QT       += core gui xml

CONFIG += c++11
QMAKE_CXXFLAGS += -std=c++0x

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Marken
TEMPLATE = app

TRANSLATIONS += lang/Lang_CH.ts

INCLUDEPATH += "./include"

SOURCES += src/main.cpp\
    src/Marken.cpp \
    src/Editor.cpp \
    src/Previewer.cpp \
    src/MarkdownHighlighter.cpp \
    src/ColorSchemeWidget.cpp \
    src/Setting.cpp \
    src/ColorSchemeSetting.cpp \
    src/ColorSchemeNode.cpp \
    src/ColorScheme.cpp \
    src/ColorWidget.cpp \
    src/HTMLGenerator.cpp \
    src/MarkdownRegex.cpp \
    src/MarkdownDefination.cpp

HEADERS  += include/Marken.h \
    include/Editor.h \
    include/Previewer.h \
    include/MarkdownHighlighter.h \
    include/ColorSchemeWidget.h \
    include/Setting.h \
    include/ColorSchemeSetting.h \
    include/ColorSchemeNode.h \
    include/ColorScheme.h \
    include/ColorWidget.h \
    include/HTMLGenerator.h \
    include/MarkdownRegex.h \
    include/MarkdownDefination.h

FORMS    += form/Marken.ui \
    form/Editor.ui \
    form/Previewer.ui \
    form/ColorSchemeWidget.ui
