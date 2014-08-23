#include "MarkdownHighlighter.h"

bool MarkdownHighlighter::isAtxHeader(const QString &text, MarkdownBlockData *data) {
    QRegExp header1("^#([^#].*|$)");
    QRegExp header2("^#{2}([^#].*|$)");
    QRegExp header3("^#{3}([^#].*|$)");
    QRegExp header4("^#{4}([^#].*|$)");
    QRegExp header5("^#{5}([^#].*|$)");
    QRegExp header6("^#{6}([^#].*|$)");
    if (header1.indexIn(text) == 0) {
        this->setFormat(0, text.length(), Setting::instance()->colorScheme.format(MarkdownDefination::getString(MarkdownDefination::ATX_HEADER_1)));
        data->setType(MarkdownBlockData::LINE_ATX_HEADER_1);
        return true;
    }
    if (header2.indexIn(text) == 0) {
        this->setFormat(0, text.length(), Setting::instance()->colorScheme.format(MarkdownDefination::getString(MarkdownDefination::ATX_HEADER_1)));
        data->setType(MarkdownBlockData::LINE_ATX_HEADER_2);
        return true;
    }
    if (header3.indexIn(text) == 0) {
        this->setFormat(0, text.length(), Setting::instance()->colorScheme.format(MarkdownDefination::getString(MarkdownDefination::ATX_HEADER_1)));
        data->setType(MarkdownBlockData::LINE_ATX_HEADER_3);
        return true;
    }
    if (header4.indexIn(text) == 0) {
        this->setFormat(0, text.length(), Setting::instance()->colorScheme.format(MarkdownDefination::getString(MarkdownDefination::ATX_HEADER_1)));
        data->setType(MarkdownBlockData::LINE_ATX_HEADER_4);
        return true;
    }
    if (header5.indexIn(text) == 0) {
        this->setFormat(0, text.length(), Setting::instance()->colorScheme.format(MarkdownDefination::getString(MarkdownDefination::ATX_HEADER_1)));
        data->setType(MarkdownBlockData::LINE_ATX_HEADER_5);
        return true;
    }
    if (header6.indexIn(text) == 0) {
        this->setFormat(0, text.length(), Setting::instance()->colorScheme.format(MarkdownDefination::getString(MarkdownDefination::ATX_HEADER_1)));
        data->setType(MarkdownBlockData::LINE_ATX_HEADER_6);
        return true;
    }
    return false;
}
