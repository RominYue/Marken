#ifndef MARKDOWNHIGHLIGHTER_H
#define MARKDOWNHIGHLIGHTER_H

#include <QSharedPointer>
#include <QSyntaxHighlighter>
#include "DynamicParser.h"

class Highlighter : public QSyntaxHighlighter {
    Q_OBJECT
public:
    Highlighter(QTextDocument *parent);
    void setParser(QSharedPointer<DynamicParser> parser);

    void highlightBlock(const QString& text);

private:
    QSharedPointer<DynamicParser> _parser;

    void highlight(QTextBlock block);
};

#endif // MARKDOWNHIGHLIGHTER_H
