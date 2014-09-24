#-------------------------------------------------
#
# Project created by QtCreator 2014-09-08T16:16:08
#
#-------------------------------------------------

QT       += core

QT       -= gui

TARGET = Parser
CONFIG   += console
CONFIG   += C++11
CONFIG   -= app_bundle

TEMPLATE = app

INCLUDEPATH += "./include"
INCLUDEPATH += "./include/common"
INCLUDEPATH += "./include/block"
INCLUDEPATH += "./include/span"
INCLUDEPATH += "./include/parser"

SOURCES += \
    src/block/ParseElementBlock.cpp \
    src/block/ParseElementCodeBlock.cpp \
    src/block/ParseElementCodeFence.cpp \
    src/block/ParseElementHeader.cpp \
    src/block/ParseElementHeaderAtx.cpp \
    src/block/ParseElementHeaderSetext.cpp \
    src/block/ParseElementHorizontal.cpp \
    src/block/ParseElementHtmlBlock.cpp \
    src/block/ParseElementLinkLabel.cpp \
    src/block/ParseElementList.cpp \
    src/block/ParseElementListOrdered.cpp \
    src/block/ParseElementListUnordered.cpp \
    src/block/ParseElementParagraph.cpp \
    src/block/ParseElementQuote.cpp \
    src/common/ParseElement.cpp \
    src/common/ParseElementFactory.cpp \
    src/common/ParseElementHtml.cpp \
    src/common/ParseElementLink.cpp \
    src/common/ParseLabelSet.cpp \
    src/common/ParseLineData.cpp \
    src/parser/DynamicParser.cpp \
    src/parser/SpanParser.cpp \
    src/parser/StaticParser.cpp \
    src/span/ParseElementAmp.cpp \
    src/span/ParseElementCodeInline.cpp \
    src/span/ParseElementEmphasis.cpp \
    src/span/ParseElementEmpty.cpp \
    src/span/ParseElementEscape.cpp \
    src/span/ParseElementHtmlInline.cpp \
    src/span/ParseElementImage.cpp \
    src/span/ParseElementImageInline.cpp \
    src/span/ParseElementImageReference.cpp \
    src/span/ParseElementLinkAutomatic.cpp \
    src/span/ParseElementLinkInline.cpp \
    src/span/ParseElementLinkReference.cpp \
    src/span/ParseElementPlain.cpp \
    src/span/ParseElementSpan.cpp \
    src/span/ParseElementStrong.cpp \
    main.cpp

HEADERS += \
    include/block/ParseElementBlock.h \
    include/block/ParseElementCodeBlock.h \
    include/block/ParseElementCodeFence.h \
    include/block/ParseElementHeader.h \
    include/block/ParseElementHeaderAtx.h \
    include/block/ParseElementHeaderSetext.h \
    include/block/ParseElementHorizontal.h \
    include/block/ParseElementHtmlBlock.h \
    include/block/ParseElementLinkLabel.h \
    include/block/ParseElementList.h \
    include/block/ParseElementListOrdered.h \
    include/block/ParseElementListUnordered.h \
    include/block/ParseElementParagraph.h \
    include/block/ParseElementQuote.h \
    include/common/ParseElement.h \
    include/common/ParseElementFactory.h \
    include/common/ParseElementHtml.h \
    include/common/ParseElementLink.h \
    include/common/ParseElementType.h \
    include/common/ParseLabelSet.h \
    include/common/ParseLineData.h \
    include/parser/DynamicParser.h \
    include/parser/SpanParser.h \
    include/parser/StaticParser.h \
    include/span/ParseElementAmp.h \
    include/span/ParseElementCodeInline.h \
    include/span/ParseElementEmphasis.h \
    include/span/ParseElementEmpty.h \
    include/span/ParseElementEscape.h \
    include/span/ParseElementHtmlInline.h \
    include/span/ParseElementImage.h \
    include/span/ParseElementImageInline.h \
    include/span/ParseElementImageReference.h \
    include/span/ParseElementLinkAutomatic.h \
    include/span/ParseElementLinkInline.h \
    include/span/ParseElementLinkReference.h \
    include/span/ParseElementPlain.h \
    include/span/ParseElementSpan.h \
    include/span/ParseElementStrong.h
