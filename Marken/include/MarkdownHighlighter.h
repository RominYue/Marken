#ifndef MARKDOWNHIGHLIGHTER_H
#define MARKDOWNHIGHLIGHTER_H

#include <QSyntaxHighlighter>
#include "MarkdownRegex.h"

class MarkdownHighlighter : public QSyntaxHighlighter {
    Q_OBJECT
public:
    explicit MarkdownHighlighter(QTextDocument *parent = 0);

protected:
    void highlightBlock(const QString &text) override final;

private:
    MarkdownRegex _regex;
};

#endif // MARKDOWNHIGHLIGHTER_H
