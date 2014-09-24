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

RC_FILE = resource.rc

TRANSLATIONS += lang/Lang_CH.ts

INCLUDEPATH += "./include"
INCLUDEPATH += "../Parser"
INCLUDEPATH += "../Parser/include"
INCLUDEPATH += "../Parser/include/block"
INCLUDEPATH += "../Parser/include/common"
INCLUDEPATH += "../Parser/include/parser"
INCLUDEPATH += "../Parser/include/span"

SOURCES += src/main.cpp\
    src/Marken.cpp \
    src/ColorWidget.cpp \
    src/Preview.cpp \
    src/LineNumberArea.cpp \
    src/BlockData.cpp \
    src/Editor.cpp \
    src/Highlighter.cpp \
    src/TabWidget.cpp \
    src/ColorSchemeForm.cpp \
    src/ColorScheme.cpp \
    src/ColorSchemeSetting.cpp \
    src/Setting.cpp \
    ../Parser/src/block/ParseElementBlock.cpp \
    ../Parser/src/block/ParseElementCodeBlock.cpp \
    ../Parser/src/block/ParseElementCodeFence.cpp \
    ../Parser/src/block/ParseElementHeader.cpp \
    ../Parser/src/block/ParseElementHeaderAtx.cpp \
    ../Parser/src/block/ParseElementHeaderSetext.cpp \
    ../Parser/src/block/ParseElementHorizontal.cpp \
    ../Parser/src/block/ParseElementHtmlBlock.cpp \
    ../Parser/src/block/ParseElementLinkLabel.cpp \
    ../Parser/src/block/ParseElementList.cpp \
    ../Parser/src/block/ParseElementListOrdered.cpp \
    ../Parser/src/block/ParseElementListUnordered.cpp \
    ../Parser/src/block/ParseElementParagraph.cpp \
    ../Parser/src/block/ParseElementQuote.cpp \
    ../Parser/src/common/ParseElement.cpp \
    ../Parser/src/common/ParseElementFactory.cpp \
    ../Parser/src/common/ParseElementHtml.cpp \
    ../Parser/src/common/ParseElementLink.cpp \
    ../Parser/src/common/ParseLabelSet.cpp \
    ../Parser/src/common/ParseLineData.cpp \
    ../Parser/src/parser/DynamicParser.cpp \
    ../Parser/src/parser/SpanParser.cpp \
    ../Parser/src/parser/StaticParser.cpp \
    ../Parser/src/span/ParseElementAmp.cpp \
    ../Parser/src/span/ParseElementCodeInline.cpp \
    ../Parser/src/span/ParseElementEmphasis.cpp \
    ../Parser/src/span/ParseElementEmpty.cpp \
    ../Parser/src/span/ParseElementEscape.cpp \
    ../Parser/src/span/ParseElementHtmlInline.cpp \
    ../Parser/src/span/ParseElementImage.cpp \
    ../Parser/src/span/ParseElementImageInline.cpp \
    ../Parser/src/span/ParseElementImageReference.cpp \
    ../Parser/src/span/ParseElementLinkAutomatic.cpp \
    ../Parser/src/span/ParseElementLinkInline.cpp \
    ../Parser/src/span/ParseElementLinkReference.cpp \
    ../Parser/src/span/ParseElementPlain.cpp \
    ../Parser/src/span/ParseElementSpan.cpp \
    ../Parser/src/span/ParseElementStrong.cpp

HEADERS  += include/Marken.h \
    include/ColorWidget.h \
    include/Preview.h \
    include/LineNumberArea.h \
    include/BlockData.h \
    include/Editor.h \
    include/Highlighter.h \
    include/TabWidget.h \
    include/ColorSchemeForm.h \
    include/ColorScheme.h \
    include/ColorSchemeSetting.h \
    include/Setting.h \
    ../Parser/include/block/ParseElementBlock.h \
    ../Parser/include/block/ParseElementCodeBlock.h \
    ../Parser/include/block/ParseElementCodeFence.h \
    ../Parser/include/block/ParseElementHeader.h \
    ../Parser/include/block/ParseElementHeaderAtx.h \
    ../Parser/include/block/ParseElementHeaderSetext.h \
    ../Parser/include/block/ParseElementHorizontal.h \
    ../Parser/include/block/ParseElementHtmlBlock.h \
    ../Parser/include/block/ParseElementLinkLabel.h \
    ../Parser/include/block/ParseElementList.h \
    ../Parser/include/block/ParseElementListOrdered.h \
    ../Parser/include/block/ParseElementListUnordered.h \
    ../Parser/include/block/ParseElementParagraph.h \
    ../Parser/include/block/ParseElementQuote.h \
    ../Parser/include/common/ParseElement.h \
    ../Parser/include/common/ParseElementFactory.h \
    ../Parser/include/common/ParseElementHtml.h \
    ../Parser/include/common/ParseElementLink.h \
    ../Parser/include/common/ParseElementType.h \
    ../Parser/include/common/ParseLabelSet.h \
    ../Parser/include/common/ParseLineData.h \
    ../Parser/include/parser/DynamicParser.h \
    ../Parser/include/parser/SpanParser.h \
    ../Parser/include/parser/StaticParser.h \
    ../Parser/include/span/ParseElementAmp.h \
    ../Parser/include/span/ParseElementCodeInline.h \
    ../Parser/include/span/ParseElementEmphasis.h \
    ../Parser/include/span/ParseElementEmpty.h \
    ../Parser/include/span/ParseElementEscape.h \
    ../Parser/include/span/ParseElementHtmlInline.h \
    ../Parser/include/span/ParseElementImage.h \
    ../Parser/include/span/ParseElementImageInline.h \
    ../Parser/include/span/ParseElementImageReference.h \
    ../Parser/include/span/ParseElementLinkAutomatic.h \
    ../Parser/include/span/ParseElementLinkInline.h \
    ../Parser/include/span/ParseElementLinkReference.h \
    ../Parser/include/span/ParseElementPlain.h \
    ../Parser/include/span/ParseElementSpan.h \
    ../Parser/include/span/ParseElementStrong.h

FORMS    += form/Marken.ui \
    form/Preview.ui \
    form/ColorSchemeForm.ui

RESOURCES += \
    icons.qrc
