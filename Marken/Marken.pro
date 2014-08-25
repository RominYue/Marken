#-------------------------------------------------
#
# Project created by QtCreator 2014-08-21T09:11:35
#
#-------------------------------------------------

QT       += core gui xml

CONFIG += c++11
QMAKE_CXXFLAGS += -std=c++0x
QMAKE_LFLAGS = -static

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Marken
TEMPLATE = app

RC_FILE = resource.rc

TRANSLATIONS += lang/Lang_CH.ts

INCLUDEPATH += "./include"

SOURCES += src/main.cpp\
    src/Marken.cpp \
    src/Previewer.cpp \
    src/MarkdownHighlighter.cpp \
    src/ColorSchemeWidget.cpp \
    src/Setting.cpp \
    src/ColorSchemeSetting.cpp \
    src/ColorSchemeNode.cpp \
    src/ColorScheme.cpp \
    src/ColorWidget.cpp \
    src/MarkdownRegex.cpp \
    src/MarkdownEditor.cpp \
    src/MarkdownBlockData.cpp \
    src/MarkdownDefine.cpp \
    src/MarkdownDebug.cpp \
    src/MarkdownParser.cpp \
    src/MarkdownTabWidget.cpp

HEADERS  += include/Marken.h \
    include/Previewer.h \
    include/MarkdownHighlighter.h \
    include/ColorSchemeWidget.h \
    include/Setting.h \
    include/ColorSchemeSetting.h \
    include/ColorSchemeNode.h \
    include/ColorScheme.h \
    include/ColorWidget.h \
    include/MarkdownRegex.h \
    include/MarkdownEditor.h \
    include/MarkdownBlockData.h \
    include/MarkdownDefine.h \
    include/MarkdownDebug.h \
    include/MarkdownParser.h \
    include/MarkdownTabWidget.h

FORMS    += form/Marken.ui \
    form/Previewer.ui \
    form/ColorSchemeWidget.ui

RESOURCES += \
    icons.qrc
