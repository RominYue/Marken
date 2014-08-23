#include "MarkdownHighlighter.h"

bool MarkdownHighlighter::isCodeBlockFormat(const QString &text, MarkdownBlockData *data) {
    QRegExp spaces("^(\\s{4}|\\t)");
    if (spaces.indexIn(text) == 0) {
        int length = spaces.matchedLength();
        this->setFormat(0, length,
                        Setting::instance()->colorScheme.format(MarkdownDefination::getString(MarkdownDefination::CODE_BLOCK)));
        data->setType(MarkdownBlockData::LINE_CODE_BLOCK);
        return true;
    }
    return false;
}
