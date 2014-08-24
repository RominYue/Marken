#include <QTextBlock>
#include <QTextDocument>
#include <QTextCursor>
#include "MarkdownHighlighter.h"

MarkdownHighlighter::MarkdownHighlighter(QTextDocument *parent) :
    QSyntaxHighlighter(parent) {
    this->_atxHeader1 = QRegExp("#([^#].*|$)");
    this->_atxHeader2 = QRegExp("#{2}([^#].*|$)");
    this->_atxHeader3 = QRegExp("#{3}([^#].*|$)");
    this->_atxHeader4 = QRegExp("#{4}([^#].*|$)");
    this->_atxHeader5 = QRegExp("#{5}([^#].*|$)");
    this->_atxHeader6 = QRegExp("#{6}([^#].*|$)");
    this->_setextHeader1 = QRegExp("=+$");
    this->_setextHeader2 = QRegExp("-+$");
    this->_blockHtmlBegin = QRegExp("<(address|blockquote|ol|p|pre|table|ul)>$");
    this->_blockHtmlEnd = QRegExp("</(address|blockquote|ol|p|pre|table|ul)>$");
    this->_codeblock = QRegExp("(\\s{4}|\\t)");
    this->_horizon = QRegExp("(\\*[\\s\\t]*){3,}|(-[\\s\\t]*){3,}|(_[\\s\\t]*){3,}$");
    this->_unorderedList = QRegExp("[\\*\\+-][\\s\\t]");
    this->_orderedList = QRegExp("\\d+\\.[\\s\\t]");
    this->_quote = QRegExp(">[\\s\\t]");
}

void MarkdownHighlighter::highlightBlock(const QString &text) {
    QTextBlock block = this->currentBlock();
    MarkdownBlockData* data = dynamic_cast<MarkdownBlockData*>(block.userData());
    if (data == nullptr) {
        data = new MarkdownBlockData();
        this->setCurrentBlockUserData(data);
    }
    data->clear();
    QTextBlock prevBlock = block.previous();
    MarkdownBlockData* prev = dynamic_cast<MarkdownBlockData*>(prevBlock.userData());
    auto scheme = Setting::instance()->colorScheme;
    for (int i = 0, j = 0; i <= text.size(); ++i) {
        // Empty line, fill with block elements.
        if (i == text.size()) {
            if (prev != nullptr) {
                while (j < prev->indents()->size()) {
                    if (i <= prev->indent(j)) {
                        if (prev->type(j) == MarkdownBlockData::LINE_BLOCK_QUOTE ||
                            prev->type(j) == MarkdownBlockData::LINE_UNORDERED_LIST ||
                            prev->type(j) == MarkdownBlockData::LINE_ORDERED_LIST) {
                            data->types()->append(prev->type(j));
                            data->indents()->append(prev->indent(j));
                        }
                    }
                    ++j;
                }
            }
            if (data->types()->size() == 0) {
                data->types()->append(MarkdownBlockData::LINE_EMPTY);
                data->indents()->append(0);
            }
            break;
        }
        // Code block.
        if (prev != nullptr && prev->lastIndent() == i) {
            if (this->_codeblock.indexIn(text, i) == i) {
                int length = this->_codeblock.matchedLength();
                this->setFormat(i, length, scheme.format(MarkdownDefine::CODE_BLOCK));
                data->types()->append(MarkdownBlockData::LINE_CODE_BLOCK);
                data->indents()->append(i);
                data->setLastIndent(i);
                break;
            }
        }
        // Atx headers.
        if (this->_atxHeader1.indexIn(text, i) == i) {
            int length = this->_atxHeader1.matchedLength();
            this->setFormat(i, length, scheme.format(MarkdownDefine::ATX_HEADER_1));
            data->types()->append(MarkdownBlockData::LINE_ATX_HEADER_1);
            data->indents()->append(i);
            data->setLastIndent(i);
            break;
        }
        if (this->_atxHeader2.indexIn(text, i) == i) {
            int length = this->_atxHeader2.matchedLength();
            this->setFormat(i, length, scheme.format(MarkdownDefine::ATX_HEADER_2));
            data->types()->append(MarkdownBlockData::LINE_ATX_HEADER_2);
            data->indents()->append(i);
            data->setLastIndent(i);
            break;
        }
        if (this->_atxHeader3.indexIn(text, i) == i) {
            int length = this->_atxHeader3.matchedLength();
            this->setFormat(i, length, scheme.format(MarkdownDefine::ATX_HEADER_3));
            data->types()->append(MarkdownBlockData::LINE_ATX_HEADER_3);
            data->indents()->append(i);
            data->setLastIndent(i);
            break;
        }
        if (this->_atxHeader4.indexIn(text, i) == i) {
            int length = this->_atxHeader4.matchedLength();
            this->setFormat(i, length, scheme.format(MarkdownDefine::ATX_HEADER_4));
            data->types()->append(MarkdownBlockData::LINE_ATX_HEADER_4);
            data->indents()->append(i);
            data->setLastIndent(i);
            break;
        }
        if (this->_atxHeader5.indexIn(text, i) == i) {
            int length = this->_atxHeader5.matchedLength();
            this->setFormat(i, length, scheme.format(MarkdownDefine::ATX_HEADER_5));
            data->types()->append(MarkdownBlockData::LINE_ATX_HEADER_5);
            data->indents()->append(i);
            data->setLastIndent(i);
            break;
        }
        if (this->_atxHeader6.indexIn(text, i) == i) {
            int length = this->_atxHeader6.matchedLength();
            this->setFormat(i, length, scheme.format(MarkdownDefine::ATX_HEADER_6));
            data->types()->append(MarkdownBlockData::LINE_ATX_HEADER_6);
            data->indents()->append(i);
            data->setLastIndent(i);
            break;
        }
        // Setext headers.
        if (this->_setextHeader1.indexIn(text, i) == i) {
            int length = this->_setextHeader1.matchedLength();
            this->setFormat(i, length, scheme.format(MarkdownDefine::SETEXT_HEADER_1));
            data->types()->append(MarkdownBlockData::LINE_SETEXT_HEADER_1);
            data->indents()->append(i);
            data->setLastIndent(i);
            break;
        }
        if (this->_setextHeader2.indexIn(text, i) == i) {
            int length = this->_setextHeader2.matchedLength();
            this->setFormat(i, length, scheme.format(MarkdownDefine::SETEXT_HEADER_2));
            data->types()->append(MarkdownBlockData::LINE_SETEXT_HEADER_2);
            data->indents()->append(i);
            data->setLastIndent(i);
            break;
        }
        // Horizontal.
        if (this->_horizon.indexIn(text, i) == i) {
            int length = this->_horizon.matchedLength();
            this->setFormat(i, length, scheme.format(MarkdownDefine::HORIZONTAL));
            data->types()->append(MarkdownBlockData::LINE_HORIZONTAL);
            data->indents()->append(i);
            data->setLastIndent(i);
            break;
        }
        // HTML block.
        if (prev != nullptr) {
            if (prev->types()->last() == MarkdownBlockData::LINE_BLOCK_HTML) {
                // Block level HTML element.
                if (this->_blockHtmlEnd.indexIn(text, i) == i) {
                    int length = this->_blockHtmlEnd.matchedLength();
                    QString endTag = text.mid(i + 2, length - 3);
                    data->setHtmlTag(endTag);
                    if (prev->htmlTag() == data->htmlTag()) {
                        // End of the HTML block.
                        data->types()->append(MarkdownBlockData::LINE_BLOCK_HTML_END);
                        data->indents()->append(i);
                        data->setLastIndent(i);
                        this->blockHtmlFormat(text);
                        break;
                    }
                }
                // Mid of the HTML block.
                data->types()->append(MarkdownBlockData::LINE_BLOCK_HTML);
                data->indents()->append(i);
                data->setLastIndent(i);
                data->setHtmlTag(prev->htmlTag());
                this->blockHtmlFormat(text);
                break;
            }
        }
        if (this->_blockHtmlBegin.indexIn(text, i) == i) {
            // Begin of an HTML block.
            int length = this->_blockHtmlBegin.matchedLength();
            data->types()->append(MarkdownBlockData::LINE_BLOCK_HTML);
            data->indents()->append(i);
            data->setLastIndent(i);
            QString startTag = text.mid(i + 1, length - 2);
            data->setHtmlTag(startTag);
            this->blockHtmlFormat(text);
            break;
        }
        // Unordered list.
        if (this->_unorderedList.indexIn(text, i) == i) {
            int length = this->_unorderedList.matchedLength();
            this->setFormat(i, length, scheme.format(MarkdownDefine::UNORDERED_LIST));
            data->types()->append(MarkdownBlockData::LINE_UNORDERED_LIST);
            data->indents()->append(i);
            data->setLastIndent(i + length);
            this->defaultFormat(text, i);
            break;
        }
        // Ordered list.
        if (this->_orderedList.indexIn(text, i) == i) {
            int length = this->_orderedList.matchedLength();
            this->setFormat(i, length, scheme.format(MarkdownDefine::ORDERED_LIST));
            data->types()->append(MarkdownBlockData::LINE_ORDERED_LIST);
            data->indents()->append(i);
            data->setLastIndent(i + length);
            this->defaultFormat(text, i);
            break;
        }
        // Quote.
        if (this->_quote.indexIn(text, i) == i) {
            int length = this->_quote.matchedLength();
            this->setFormat(i, length, scheme.format(MarkdownDefine::BLOCK_QUOTE));
            data->types()->append(MarkdownBlockData::LINE_BLOCK_QUOTE);
            data->indents()->append(i);
            data->setLastIndent(i + length);
            i += length - 2;
            continue;
        }
        if (text[i] == ' ' || text[i] == '\t') {
            if (prev != nullptr) {
                while (j < prev->indents()->size()) {
                    if (i >= prev->indent(j)) {
                        if (data->indents()->size() == 0 || prev->indent(j) > data->indents()->last()) {
                            if (prev->type(j) == MarkdownBlockData::LINE_BLOCK_QUOTE ||
                                prev->type(j) == MarkdownBlockData::LINE_UNORDERED_LIST ||
                                prev->type(j) == MarkdownBlockData::LINE_ORDERED_LIST) {
                                data->types()->append(prev->type(j));
                                data->indents()->append(prev->indent(j));
                            }
                        }
                    } else {
                        break;
                    }
                    ++j;
                }
            }
            continue;
        }
        // Continue paragraph.
        if (prev != nullptr && prev->types()->last() == MarkdownBlockData::LINE_DEFAULT) {
            if (data->types()->size() < prev->types()->size()) {
                *data->types() = *prev->types();
                *data->indents() = *prev->indents();
                data->setLastIndent(prev->lastIndent());
                break;
            }
        }
        // New paragraph.
        data->types()->append(MarkdownBlockData::LINE_DEFAULT);
        data->indents()->append(i);
        data->setLastIndent(i);
        this->defaultFormat(text, i);
        break;
    }
    int blockNum = this->currentBlock().blockNumber();
    emit parseBlock(blockNum);
    if (data->isStateChanged()) {
        if (blockNum > 0) {
            emit parseBlock(blockNum - 1);
        }
        this->setCurrentBlockState(this->currentBlockState() + 1);
    }
    data->recordState();
}

void MarkdownHighlighter::defaultFormat(const QString &text, int offset) {
    ColorSchemeSetting& colorScheme = Setting::instance()->colorScheme;
    auto regex = this->_regex.regex();
    for (auto name : regex.keys()) {
        QRegExp val = regex.value(name);
        int index = val.indexIn(text, offset);
        while (index >= 0) {
            int length = val.matchedLength();
            if (length == 0) {
                 break;
            }
            if (index == 0 || text[index - 1] != '\\') {
                this->setFormat(index, length, colorScheme.format(MarkdownDefine::getString(name)));
            }
            if (length == text.size() && name != MarkdownDefine::DEFAULT) {
                return;
            }
            index = val.indexIn(text, index + length);
        }
    }
}

void MarkdownHighlighter::blockHtmlFormat(const QString &text) {
    this->setFormat(0, text.length(), Setting::instance()->colorScheme.format(MarkdownDefine::BLOCK_HTML));
}
