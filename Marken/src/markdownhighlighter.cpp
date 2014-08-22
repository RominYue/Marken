#include "Setting.h"
#include "MarkdownHighlighter.h"

MarkdownHighlighter::MarkdownHighlighter(QTextDocument *parent) :
    QSyntaxHighlighter(parent) {
    this->setextHeaderRegex = QRegExp("^[=-]+$");
    this->horizontalRegex = QRegExp("^([\\*\\-_]\\W*){3,}$");
    this->orderedListRegex = QRegExp("^\\d+\\.");
    this->codeBlockRegex = QRegExp("^\\s{4}|^\\t");
    this->inlineLinkRegex = QRegExp("\\[.*\\]\\(.*\\)");
    this->inlineLinkRegex.setMinimal(true);
    this->referenceLinkRegex = QRegExp("\\[.*\\]\\[.*\\]");
    this->referenceLinkRegex.setMinimal(true);
    this->linkLabelRegex = QRegExp("^\\[.*\\]:.*$");
    this->linkLabelRegex.setMinimal(true);
    this->emphasisRegex = QRegExp("\\*.+\\*|_.+_");
    this->emphasisRegex.setMinimal(true);
    this->strongRegex = QRegExp("\\*\\*.+\\*\\*|__.+__");
    this->strongRegex.setMinimal(true);
    this->imageRegex = QRegExp("!\\[.*\\]\\[.*\\]");
    this->imageRegex.setMinimal(true);
    this->inlineCodeRegex = QRegExp("`.*`");
    this->inlineCodeRegex.setMinimal(true);
}

void MarkdownHighlighter::highlightBlock(const QString &text) {
    ColorSchemeSetting& colorScheme = Setting::instance()->colorScheme;
    setFormat(0, text.size(), colorScheme.format());
    // Atx-style header.
    int sharpNum = 0;
    for (int i = 0; i < text.size() && i < 7; ++i) {
        if (text[i] == '#') {
            ++sharpNum;
        }
    }
    if (1 <= sharpNum && sharpNum <= 6) {
        setFormat(0, text.size(), colorScheme.format(QString("Atx Header %1").arg(sharpNum)));
        return;
    }
    // Setext header.
    if (this->setextHeaderRegex.indexIn(text) == 0) {
        if (text[0] == '=') {
            setFormat(0, text.size(), colorScheme.format("Setext Header 1"));
        } else {
            setFormat(0, text.size(), colorScheme.format("Setext Header 2"));
        }
        return;
    }
    // Horizon line.
    if (this->horizontalRegex.indexIn(text) == 0) {
        setFormat(0, text.size(), colorScheme.format("Horizontal"));
        return;
    }
    // Block-quote.
    if (text.size() > 0) {
        if (text[0] == '>') {
            setFormat(0, 1, colorScheme.format("Block Quote"));
        }
    }
    // Unordered list.
    if (text.size() > 0) {
        if (text[0] == '*' || text[0] == '+' || text[0] == '-') {
            setFormat(0, 1, colorScheme.format("Unordered List"));
        }
    }
    // Ordered list.
    if (this->orderedListRegex.indexIn(text) == 0) {
        int length = this->orderedListRegex.matchedLength();
        setFormat(0, length, colorScheme.format("Ordered List"));
    }
    // Code block.
    if (this->codeBlockRegex.indexIn(text) == 0) {
        int length = this->codeBlockRegex.matchedLength();
        setFormat(0, length, colorScheme.format("Code Block"));
    }
    // Inline link.
    int index = this->inlineLinkRegex.indexIn(text);
    while (index >= 0) {
        int length = this->inlineLinkRegex.matchedLength();
        if (index == 0 || text[index - 1] != '\\') {
            setFormat(index, length, colorScheme.format("Inline Link"));
        }
        index = this->inlineLinkRegex.indexIn(text, index + length);
    }
    // Reference link.
    index = this->referenceLinkRegex.indexIn(text);
    while (index >= 0) {
        int length = this->referenceLinkRegex.matchedLength();
        if (index == 0 || (text[index - 1] != '\\' && text[index - 1] != '!')) {
            setFormat(index, length, colorScheme.format("Reference Link"));
        }
        index = this->referenceLinkRegex.indexIn(text, index + length);
    }
    // Link label.
    index = this->linkLabelRegex.indexIn(text);
    while (index >= 0) {
        int length = this->linkLabelRegex.matchedLength();
        if (index == 0 || text[index - 1] != '\\') {
            setFormat(index, length, colorScheme.format("Link Label"));
        }
        index = this->linkLabelRegex.indexIn(text, index + length);
    }
    // Inline code.
    index = this->inlineCodeRegex.indexIn(text);
    while (index >= 0) {
        int length = this->inlineCodeRegex.matchedLength();
        if (index == 0 || text[index - 1] != '\\') {
            setFormat(index, length, colorScheme.format("Inline Code"));
        }
        index = this->inlineCodeRegex.indexIn(text, index + length);
    }
    // Image.
    index = this->imageRegex.indexIn(text);
    while (index >= 0) {
        int length = this->imageRegex.matchedLength();
        if (index == 0 || text[index - 1] != '\\') {
            setFormat(index, length, colorScheme.format("Image"));
        }
        index = this->imageRegex.indexIn(text, index + length);
    }
    // Emphasis.
    index = this->emphasisRegex.indexIn(text);
    while (index >= 0) {
        int length = this->emphasisRegex.matchedLength();
        if (index == 0 || text[index - 1] != '\\') {
            setFormat(index, length, colorScheme.format("Emphasis"));
        }
        index = this->emphasisRegex.indexIn(text, index + length);
    }
    // Strong.
    index = this->strongRegex.indexIn(text);
    while (index >= 0) {
        int length = this->strongRegex.matchedLength();
        if (index == 0 || text[index - 1] != '\\') {
            setFormat(index, length, colorScheme.format("Strong"));
        }
        index = this->strongRegex.indexIn(text, index + length);
    }
}
