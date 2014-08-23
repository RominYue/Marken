#include <QTextBlock>
#include <QTextDocument>
#include <QTextCursor>
#include "Setting.h"
#include "MarkdownHighlighter.h"

MarkdownHighlighter::MarkdownHighlighter(QTextDocument *parent) :
    QSyntaxHighlighter(parent) {
}

void MarkdownHighlighter::highlightBlock(const QString &text) {
    QTextBlock block = this->currentBlock();
    MarkdownBlockData* data = dynamic_cast<MarkdownBlockData*>(block.userData());
    if (data == nullptr) {
        data = new MarkdownBlockData();
        this->setCurrentBlockUserData(data);
    }
    QTextBlock prevBlock = block.previous();
    MarkdownBlockData* prev = dynamic_cast<MarkdownBlockData*>(prevBlock.userData());
    if (this->isBlockHtmlFormat(text, data, prev)) {
        this->blockHtmlFormat(text);
    } else if (this->isNestedBlock(text, data)) {
    } else if (text.isEmpty()) {
        data->setType(MarkdownBlockData::LINE_EMPTY);
    } else if (this->isCodeBlockFormat(text, data)) {
    } else if (this->isAtxHeader(text, data)) {
    } else if (this->isSetextHeader(text, data)) {
    } else if (this->isHorizonLine(text, data)) {
    } else {
        this->defaultFormat(text);
        data->setType(MarkdownBlockData::LINE_DEFAULT);
    }
    this->setCurrentBlockState(data->type());
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
                this->setFormat(index, length, colorScheme.format(MarkdownDefination::getString(name)));
            }
            if (length == text.size() && name != MarkdownDefination::DEFAULT) {
                return;
            }
            index = val.indexIn(text, index + length);
        }
    }
}
