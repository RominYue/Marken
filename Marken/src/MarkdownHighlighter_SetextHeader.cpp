#include "MarkdownHighlighter.h"

bool MarkdownHighlighter::isSetextHeader(const QString &text, MarkdownBlockData *data) {
    QRegExp header1("^=+$");
    QRegExp header2("^-+$");
    if (header1.indexIn(text) == 0) {
        this->setFormat(0, text.length(), Setting::instance()->colorScheme.format(MarkdownDefination::getString(MarkdownDefination::SETEXT_HEADER_1)));
        data->setType(MarkdownBlockData::LINE_SETEXT_HEADER_1_END);
        return true;
    }
    if (header2.indexIn(text) == 0) {
        this->setFormat(0, text.length(), Setting::instance()->colorScheme.format(MarkdownDefination::getString(MarkdownDefination::SETEXT_HEADER_2)));
        data->setType(MarkdownBlockData::LINE_SETEXT_HEADER_2_END);
        return true;
    }
    return false;
}
