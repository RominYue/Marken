#include "MarkdownHighlighter.h"

bool MarkdownHighlighter::isHorizonLine(const QString &text, MarkdownBlockData *data) {
    QRegExp horizon("^([\\*-_]\\W*){3,}$");
    if (horizon.indexIn(text) == 0) {
        data->setType(MarkdownBlockData::LINE_HORIZONTAL);
        this->setFormat(0, text.length(), Setting::instance()->colorScheme.format(MarkdownDefination::getString(MarkdownDefination::HORIZONTAL)));
        return true;
    }
    return false;
}
