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
    } else {
        data->clear();
    }
    data->setText(text);
    QTextBlock prevBlock = block.previous();
    MarkdownBlockData* prev = dynamic_cast<MarkdownBlockData*>(prevBlock.userData());
    if (this->isBlockHtmlFormat(text, data, prev)) {
        this->blockHtmlFormat(text);
    } else if (this->isCodeBlockFormat(text, data, prev)) {
    } else if (this->isAtxHeader(text, data)) {
    } else if (this->isSetextHeader(text, data)) {
    } else if (this->isHorizonLine(text, data)) {
    } else {
        this->defaultFormat(text);
        data->setType(MarkdownBlockData::LINE_DEFAULT);
    }
    data->generateHtml();
    this->setCurrentBlockState(data->firstType());
}

void MarkdownHighlighter::defaultFormat(const QString &text) {
    ColorSchemeSetting& colorScheme = Setting::instance()->colorScheme;
    auto regex = this->_regex.regex();
    for (auto name : regex.keys()) {
        QRegExp val = regex.value(name);
        int index = val.indexIn(text);
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
