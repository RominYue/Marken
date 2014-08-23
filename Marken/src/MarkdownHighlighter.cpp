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
    if (data != nullptr) {
        delete data;
    }
    data = new MarkdownBlockData();
    data->setText(text);
    QTextBlock prevBlock = block.previous();
    MarkdownBlockData* prev = dynamic_cast<MarkdownBlockData*>(prevBlock.userData());
    if (this->isBlockHtmlFormat(text, data, prev)) {
        this->blockHtmlFormat(text);
    } else if (this->isCodeBlockFormat(text, data, prev)) {
    } else {
        data->setType(MarkdownBlockData::LINE_DEFAULT);
    }
    data->generateHtml();
    this->setCurrentBlockUserData(data);
    this->setCurrentBlockState(data->firstType());
}
