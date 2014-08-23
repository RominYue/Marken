#include "MarkdownHighlighter.h"

bool MarkdownHighlighter::isCodeBlockFormat(const QString &text, MarkdownBlockData *data, MarkdownBlockData *prev) {
    QRegExp spaces("^(\\s{4}|\\t)");
    if (spaces.indexIn(text) == 0) {
        int length = spaces.matchedLength();
        this->setFormat(0, length,
                        Setting::instance()->colorScheme.format(MarkdownDefination::getString(MarkdownDefination::CODE_BLOCK)));
        switch (prev->firstType()) {
        case MarkdownBlockData::LINE_CODE_BLOCK_SINGLE:
            prev->setType(MarkdownBlockData::LINE_CODE_BLOCK_BEGIN);
            data->setType(MarkdownBlockData::LINE_CODE_BLOCK_END);
            prev->generateHtml();
            break;
        case MarkdownBlockData::LINE_CODE_BLOCK_BEGIN:
        case MarkdownBlockData::LINE_CODE_BLOCK_MID:
            data->setType(MarkdownBlockData::LINE_CODE_BLOCK_END);
            break;
        case MarkdownBlockData::LINE_CODE_BLOCK_END:
            prev->setType(MarkdownBlockData::LINE_CODE_BLOCK_MID);
            data->setType(MarkdownBlockData::LINE_CODE_BLOCK_END);
            prev->generateHtml();
            break;
        default:
            data->setType(MarkdownBlockData::LINE_CODE_BLOCK_SINGLE);
            break;
        }
        return true;
    }
    return false;
}
