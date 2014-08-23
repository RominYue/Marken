#-------------------------------------------------
#
# Project created by QtCreator 2014-08-21T09:11:35
#
#-------------------------------------------------

QT       += core gui xml webkit webkitwidgets

CONFIG += c++11
QMAKE_CXXFLAGS += -std=c++0x

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Marken
TEMPLATE = app

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
    src/MarkdownDefination.cpp \
    src/MarkdownEditor.cpp \
    src/MarkdownBlockData.cpp \
    src/MarkdownHighlighter_BlockHtml.cpp \
    src/MarkdownHighlighter_CodeBlock.cpp \
    src/MarkdownHighlighter_AtxHeader.cpp \
    src/MarkdownHighlighter_SetextHeader.cpp \
    src/MarkdownHighlighter_HorizonLine.cpp \
    src/MarkdownHighlighter_NestedBlock.cpp \
    src/MarkdownParser.cpp

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
    include/MarkdownDefination.h \
    include/MarkdownEditor.h \
    include/MarkdownBlockData.h \
    include/MarkdownParser.h

FORMS    += form/Marken.ui \
    form/Previewer.ui \
    form/ColorSchemeWidget.ui

RESOURCES += \
    icons.qrc
