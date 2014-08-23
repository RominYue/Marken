#include "MarkdownHighlighter.h"

bool MarkdownHighlighter::isBlockHtmlFormat(const QString &text, MarkdownBlockData *data, MarkdownBlockData *prev) {
    QRegExp beginTagRegex("^<(address|blockquote|ol|p|pre|table|ul)>$");
    QRegExp endTagRegex("^</(address|blockquote|ol|p|pre|table|ul)>$");
    if (prev != nullptr) {
        if (prev->firstType() == MarkdownBlockData::LINE_BLOCK_HTML) {
            // Block level HTML element.
            int index = endTagRegex.indexIn(text);
            if (index == 0) {
                int length = endTagRegex.matchedLength();
                QString endTag = text.mid(index + 2, length - 3);
                data->setHtmlTag(endTag);
                if (prev->htmlTag() == data->htmlTag()) {
                    // End of the HTML block.
                    data->types()->append(MarkdownBlockData::LINE_BLOCK_HTML_END);
                    return true;
                }
            }
            // Mid of the HTML block.
            data->types()->append(MarkdownBlockData::LINE_BLOCK_HTML);
            data->setHtmlTag(prev->htmlTag());
            return true;
        }
    }
    int index = beginTagRegex.indexIn(text);
    if (index == 0) {
        // Begin of an HTML block.
        int length = beginTagRegex.matchedLength();
        data->types()->append(MarkdownBlockData::LINE_BLOCK_HTML);
        QString startTag = text.mid(index + 1, length - 2);
        data->setHtmlTag(startTag);
        return true;
    }
    return false;
}

void MarkdownHighlighter::blockHtmlFormat(const QString &text) {
    this->setFormat(0, text.length(),
                    Setting::instance()->colorScheme.format(MarkdownDefination::getString(MarkdownDefination::BLOCK_HTML)));
}
