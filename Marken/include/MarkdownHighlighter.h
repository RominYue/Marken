#ifndef MARKDOWNHIGHLIGHTER_H
#define MARKDOWNHIGHLIGHTER_H

#include <QSyntaxHighlighter>
#include "MarkdownBlockData.h"
#include "MarkdownRegex.h"

class MarkdownHighlighter : public QSyntaxHighlighter {
    Q_OBJECT
public:
    explicit MarkdownHighlighter(QTextDocument *parent = 0);

protected:
    void highlightBlock(const QString &text) override final;

private:
    MarkdownRegex _regex;

    enum FormatLineType {
        TYPE_DEFAULT,
        TYPE_BLOCK_HTML,
    };

    FormatLineType getFormatLineType(const QString &text);
    bool isBlockHtmlFormat(const QString &text, MarkdownBlockData *data, MarkdownBlockData *prev);

    void defaultFormat(const QString &text);
    void blockHtmlFormat(const QString &text);
};

#endif // MARKDOWNHIGHLIGHTER_H
