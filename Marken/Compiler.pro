#-------------------------------------------------
#
# Project created by QtCreator 2014-08-22T14:39:56
#
#-------------------------------------------------

QT       += core

debug {
  QT += testlib
}

QT       -= gui

TARGET = mdc
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app

CONFIG += c++11
QMAKE_CXXFLAGS += -std=c++0x

INCLUDEPATH += "./include"

SOURCES += \
    src/MarkdownDefination.cpp \
    src/MarkdownRegex.cpp \
    src/MarkdownTest.cpp \
    src/MarkdownCompiler.cpp \
    src/main_mdc.cpp

HEADERS += \
    include/MarkdownDefination.h \
    include/MarkdownRegex.h \
    include/MarkdownTest.h \
    include/MarkdownCompiler.h
