#ifndef MARKDOWNHIGHLIGHTER_H
#define MARKDOWNHIGHLIGHTER_H

#include <QSyntaxHighlighter>
#include "MarkdownBlockData.h"
#include "MarkdownRegex.h"
#include "Setting.h"

class MarkdownHighlighter : public QSyntaxHighlighter {
    Q_OBJECT
public:
    explicit MarkdownHighlighter(QTextDocument *parent = 0);

protected:
    void highlightBlock(const QString &text) override final;

private:
    MarkdownRegex _regex;

    QRegExp _atxHeader1;
    QRegExp _atxHeader2;
    QRegExp _atxHeader3;
    QRegExp _atxHeader4;
    QRegExp _atxHeader5;
    QRegExp _atxHeader6;
    QRegExp _setextHeader1;
    QRegExp _setextHeader2;
    QRegExp _blockHtmlBegin;
    QRegExp _blockHtmlEnd;
    QRegExp _codeblock;
    QRegExp _horizon;
    QRegExp _unorderedList;
    QRegExp _orderedList;
    QRegExp _quote;

    bool isBlockHtmlFormat(const QString &text, MarkdownBlockData *data, MarkdownBlockData *prev);
    bool isCodeBlockFormat(const QString &text, MarkdownBlockData *data);
    bool isAtxHeader(const QString &text, MarkdownBlockData *data);
    bool isSetextHeader(const QString &text, MarkdownBlockData *data);
    bool isHorizonLine(const QString &text, MarkdownBlockData *data);
    bool isNestedBlock(const QString &text, MarkdownBlockData *data);

    void defaultFormat(const QString &text, int offset = 0);
    void blockHtmlFormat(const QString &text);
};

#endif // MARKDOWNHIGHLIGHTER_H
