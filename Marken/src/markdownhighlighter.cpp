#include "markdownhighlighter.h"

MarkdownHighlighter::MarkdownHighlighter(QTextDocument *parent) :
    QSyntaxHighlighter(parent) {
    this->setextHeaderRegex = QRegExp("^[=-]+$");
    this->horizontalRegex = QRegExp("^([\\*\\-_]\\W*){3,}$");
    this->orderedListRegex = QRegExp("^\\d+\\.");
    this->codeBlockRegex = QRegExp("^\\s{4,}|^\\t");
    this->inlineLinkRegex = QRegExp("\\[.*\\]\\(.*\\)");
    this->inlineLinkRegex.setMinimal(true);
    this->referenceLinkRegex = QRegExp("\\[.*\\]\\[.*\\]");
    this->referenceLinkRegex.setMinimal(true);
    this->linkLabelRegex = QRegExp("^\\[.*\\]:.*$");
    this->linkLabelRegex.setMinimal(true);
    this->emEmphasisRegex = QRegExp("\\*.+\\*|_.+_");
    this->emEmphasisRegex.setMinimal(true);
    this->strongEmphasisRegex = QRegExp("\\*\\*.+\\*\\*|__.+__");
    this->strongEmphasisRegex.setMinimal(true);
    this->imageRegex = QRegExp("!\\[.*\\]\\[.*\\]");
    this->imageRegex.setMinimal(true);
    this->inlineCodeRegex = QRegExp("`.*`");
    this->inlineCodeRegex.setMinimal(true);
}

void MarkdownHighlighter::highlightBlock(const QString &text) {
    QTextCharFormat format;
    // Atx-style header.
    int sharpNum = 0;
    for (int i = 0; i < text.size() && i < 7; ++i) {
        if (text[i] == '#') {
            ++sharpNum;
        }
    }
    if (1 <= sharpNum && sharpNum <= 6) {
        format.setForeground(Qt::darkBlue);
        format.setFontWeight(QFont::Bold);
        setFormat(0, text.size(), format);
        return;
    }
    // Setext header.
    if (this->setextHeaderRegex.indexIn(text) == 0) {
        if (text[0] == '=') {
            format.setForeground(Qt::darkBlue);
            format.setFontWeight(QFont::Bold);
            setFormat(0, text.size(), format);
        } else {
            format.setForeground(Qt::darkBlue);
            format.setFontWeight(QFont::Bold);
            setFormat(0, text.size(), format);
        }
        return;
    }
    // Horizon line.
    if (this->horizontalRegex.indexIn(text) == 0) {
        format.setForeground(Qt::darkGreen);
        format.setFontWeight(QFont::Bold);
        setFormat(0, text.size(), format);
        return;
    }
    // Block-quote.
    if (text.size() > 0) {
        if (text[0] == '>') {
            format.setForeground(Qt::darkYellow);
            format.setFontWeight(QFont::Normal);
            setFormat(0, 1, format);
        }
    }
    // Unordered list.
    if (text.size() > 0) {
        if (text[0] == '*' || text[0] == '+' || text[0] == '-') {
            format.setForeground(Qt::darkYellow);
            format.setFontWeight(QFont::Normal);
            setFormat(0, 1, format);
        }
    }
    // Ordered list.
    if (this->orderedListRegex.indexIn(text) == 0) {
        int length = this->orderedListRegex.matchedLength();
        format.setForeground(Qt::darkYellow);
        format.setFontWeight(QFont::Normal);
        setFormat(0, length, format);
    }
    // Code block.
    if (this->codeBlockRegex.indexIn(text) == 0) {
        int length = this->codeBlockRegex.matchedLength();
        format.setForeground(Qt::darkYellow);
        format.setFontWeight(QFont::Normal);
        setFormat(0, length, format);
    }
    // Inline link.
    format.setForeground(Qt::darkGreen);
    format.setFontWeight(QFont::Normal);
    int index = this->inlineLinkRegex.indexIn(text);
    while (index >= 0) {
        int length = this->inlineLinkRegex.matchedLength();
        if (index == 0 || text[index - 1] != '\\') {
            setFormat(index, length, format);
        }
        index = this->inlineLinkRegex.indexIn(text, index + length);
    }
    // Reference link.
    format.setForeground(Qt::darkCyan);
    index = this->referenceLinkRegex.indexIn(text);
    while (index >= 0) {
        int length = this->referenceLinkRegex.matchedLength();
        if (index == 0 || (text[index - 1] != '\\' && text[index - 1] != '!')) {
            setFormat(index, length, format);
        }
        index = this->referenceLinkRegex.indexIn(text, index + length);
    }
    // Link label.
    format.setForeground(Qt::darkMagenta);
    index = this->linkLabelRegex.indexIn(text);
    while (index >= 0) {
        int length = this->linkLabelRegex.matchedLength();
        if (index == 0 || text[index - 1] != '\\') {
            setFormat(index, length, format);
        }
        index = this->linkLabelRegex.indexIn(text, index + length);
    }
    // Inline code.
    format.setForeground(Qt::darkRed);
    index = this->inlineCodeRegex.indexIn(text);
    while (index >= 0) {
        int length = this->inlineCodeRegex.matchedLength();
        if (index == 0 || text[index - 1] != '\\') {
            setFormat(index, length, format);
        }
        index = this->inlineCodeRegex.indexIn(text, index + length);
    }
    // Image.
    index = this->imageRegex.indexIn(text);
    while (index >= 0) {
        int length = this->imageRegex.matchedLength();
        if (index == 0 || text[index - 1] != '\\') {
            setFormat(index, length, format);
        }
        index = this->imageRegex.indexIn(text, index + length);
    }
    // Emphasis em.
    format.setFontItalic(true);
    index = this->emEmphasisRegex.indexIn(text);
    while (index >= 0) {
        int length = this->emEmphasisRegex.matchedLength();
        if (index == 0 || text[index - 1] != '\\') {
            setFormat(index, length, format);
        }
        index = this->emEmphasisRegex.indexIn(text, index + length);
    }
    // Emphasis strong.
    format.setFontItalic(false);
    format.setFontWeight(QFont::Bold);
    index = this->strongEmphasisRegex.indexIn(text);
    while (index >= 0) {
        int length = this->strongEmphasisRegex.matchedLength();
        if (index == 0 || text[index - 1] != '\\') {
            setFormat(index, length, format);
        }
        index = this->strongEmphasisRegex.indexIn(text, index + length);
    }
}
