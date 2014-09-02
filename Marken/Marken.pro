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
INCLUDEPATH += "../Parser"

SOURCES += src/main.cpp\
    src/Marken.cpp \
    src/Previewer.cpp \
    src/ColorWidget.cpp \
    src/MarkdownEditor.cpp \
    src/MarkdownTabWidget.cpp \
    ../Parser/parse.cpp \
    ../Parser/parse_dynamic.cpp \
    ../Parser/parse_elem.cpp \
    ../Parser/parse_elem_amp.cpp \
    ../Parser/parse_elem_block.cpp \
    ../Parser/parse_elem_code_block.cpp \
    ../Parser/parse_elem_code_inline.cpp \
    ../Parser/parse_elem_emphasis.cpp \
    ../Parser/parse_elem_empty.cpp \
    ../Parser/parse_elem_escape.cpp \
    ../Parser/parse_elem_factory.cpp \
    ../Parser/parse_elem_header.cpp \
    ../Parser/parse_elem_header_atx.cpp \
    ../Parser/parse_elem_header_setext.cpp \
    ../Parser/parse_elem_horizontal.cpp \
    ../Parser/parse_elem_html.cpp \
    ../Parser/parse_elem_html_block.cpp \
    ../Parser/parse_elem_html_inline.cpp \
    ../Parser/parse_elem_image.cpp \
    ../Parser/parse_elem_image_inline.cpp \
    ../Parser/parse_elem_image_reference.cpp \
    ../Parser/parse_elem_link.cpp \
    ../Parser/parse_elem_link_automatic.cpp \
    ../Parser/parse_elem_link_inline.cpp \
    ../Parser/parse_elem_link_label.cpp \
    ../Parser/parse_elem_link_reference.cpp \
    ../Parser/parse_elem_list.cpp \
    ../Parser/parse_elem_list_ordered.cpp \
    ../Parser/parse_elem_list_unordered.cpp \
    ../Parser/parse_elem_paragraph.cpp \
    ../Parser/parse_elem_plain.cpp \
    ../Parser/parse_elem_quote.cpp \
    ../Parser/parse_elem_span.cpp \
    ../Parser/parse_elem_strong.cpp \
    ../Parser/parse_label_set.cpp \
    ../Parser/parse_line.cpp \
    ../Parser/parse_span.cpp \
    ../Parser/parse_static.cpp

HEADERS  += include/Marken.h \
    include/Previewer.h \
    include/ColorWidget.h \
    include/MarkdownEditor.h \
    include/MarkdownTabWidget.h \
    ../Parser/parse.h \
    ../Parser/parse_dynamic.h \
    ../Parser/parse_elem.h \
    ../Parser/parse_elem_amp.h \
    ../Parser/parse_elem_block.h \
    ../Parser/parse_elem_code_block.h \
    ../Parser/parse_elem_code_inline.h \
    ../Parser/parse_elem_emphasis.h \
    ../Parser/parse_elem_empty.h \
    ../Parser/parse_elem_escape.h \
    ../Parser/parse_elem_factory.h \
    ../Parser/parse_elem_header.h \
    ../Parser/parse_elem_header_atx.h \
    ../Parser/parse_elem_header_setext.h \
    ../Parser/parse_elem_horizontal.h \
    ../Parser/parse_elem_html.h \
    ../Parser/parse_elem_html_block.h \
    ../Parser/parse_elem_html_inline.h \
    ../Parser/parse_elem_image.h \
    ../Parser/parse_elem_image_inline.h \
    ../Parser/parse_elem_image_reference.h \
    ../Parser/parse_elem_link.h \
    ../Parser/parse_elem_link_automatic.h \
    ../Parser/parse_elem_link_inline.h \
    ../Parser/parse_elem_link_label.h \
    ../Parser/parse_elem_link_reference.h \
    ../Parser/parse_elem_list.h \
    ../Parser/parse_elem_list_ordered.h \
    ../Parser/parse_elem_list_unordered.h \
    ../Parser/parse_elem_paragraph.h \
    ../Parser/parse_elem_plain.h \
    ../Parser/parse_elem_quote.h \
    ../Parser/parse_elem_span.h \
    ../Parser/parse_elem_strong.h \
    ../Parser/parse_elem_type.h \
    ../Parser/parse_label_set.h \
    ../Parser/parse_line.h \
    ../Parser/parse_span.h \
    ../Parser/parse_static.h

FORMS    += form/Marken.ui \
    form/Previewer.ui \
    form/ColorSchemeWidget.ui

RESOURCES += \
    icons.qrc
