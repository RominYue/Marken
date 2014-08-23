#include <QTextBlock>
#include <QTextDocument>
#include <QTextCursor>
#include "Setting.h"
#include "MarkdownHighlighter.h"

MarkdownHighlighter::MarkdownHighlighter(QTextDocument *parent) :
    QSyntaxHighlighter(parent) {
}

void MarkdownHighlighter::highlightBlock(const QString &text) {
    FormatLineType state = getFormatLineType(text);
    switch (state) {
    case TYPE_DEFAULT:
        this->defaultFormat(text);
        break;
    case TYPE_BLOCK_HTML:
        this->blockHtmlFormat(text);
        break;
    }
}

MarkdownHighlighter::FormatLineType MarkdownHighlighter::getFormatLineType(const QString &text) {
    QTextBlock block = this->currentBlock();
    MarkdownBlockData* data = dynamic_cast<MarkdownBlockData*>(block.userData());
    if (data != nullptr) {
        delete data;
    }
    data = new MarkdownBlockData();
    QTextBlock prevBlock = block.previous();
    MarkdownBlockData* prev = dynamic_cast<MarkdownBlockData*>(prevBlock.userData());
    FormatLineType formatType;
    if (this->isBlockHtmlFormat(text, data, prev)) {
        formatType = TYPE_BLOCK_HTML;
    } else {
        formatType = TYPE_DEFAULT;
        data->types()->append(MarkdownBlockData::LINE_DEFAULT);
    }
    this->setCurrentBlockUserData(data);
    this->setCurrentBlockState(data->firstType());
    return formatType;
}

void MarkdownHighlighter::defaultFormat(const QString &text) {
    // TODO
}
