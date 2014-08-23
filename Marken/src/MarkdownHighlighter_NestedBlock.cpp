#include "MarkdownHighlighter.h"

/**
 * @brief MarkdownHighlighter::isNestedBlock
 * Nested block includes quoted block <quote>, unordered list <ul>, ordered list<ol>.
 */
bool MarkdownHighlighter::isNestedBlock(const QString &text, MarkdownBlockData *data) {
    QRegExp orderedList("\\d+\\.[\\s\\t]");
    auto scheme = Setting::instance()->colorScheme;
    bool flag = false;
    int i;
    for (i = 0; i < text.size(); ++i) {
        if (text[i] == ' ' || text[i] == '\t') {
            continue;
        }
        if (text[i] == '*' || text[i] == '+' || text[i] == '-') {
            if (i + 1 >= text.length() || text[i + 1] == ' ' || text[i + 1] == '\t') {
                this->setFormat(i, 1, scheme.format(MarkdownDefination::getString(MarkdownDefination::UNORDERED_LIST)));
                flag = true;
            } else {
                break;
            }
        } else if (text[i] == '>') {
            if (i + 1 >= text.length() || text[i + 1] == ' ' || text[i + 1] == '\t') {
                this->setFormat(i, 1, scheme.format(MarkdownDefination::getString(MarkdownDefination::BLOCK_QUOTE)));
                flag = true;
            } else {
                break;
            }
        } else if (text[i] >= '0' && text[i] <= '9') {
            if (orderedList.indexIn(text, i) == i) {
                int length = orderedList.matchedLength();
                this->setFormat(i, length, scheme.format(MarkdownDefination::getString(MarkdownDefination::ORDERED_LIST)));
                flag = true;
                i += length - 1;
            } else {
                break;
            }
        } else {
            break;
        }
    }
    if (flag) {
        this->defaultFormat(text, i);
        data->setType(MarkdownBlockData::LINE_NESTED_BLOCK);
    }
    return flag;
}
