#ifndef MARKDOWNHIGHLIGHTER_H
#define MARKDOWNHIGHLIGHTER_H

#include <QSyntaxHighlighter>

class MarkdownHighlighter : public QSyntaxHighlighter {
    Q_OBJECT
public:
    explicit MarkdownHighlighter(QTextDocument *parent = 0);

protected:
    void highlightBlock(const QString &text) override final;

private:
    QRegExp setextHeaderRegex;
    QRegExp horizontalRegex;
    QRegExp orderedListRegex;
    QRegExp codeBlockRegex;
    QRegExp inlineLinkRegex;
    QRegExp referenceLinkRegex;
    QRegExp linkLabelRegex;
    QRegExp emphasisRegex;
    QRegExp strongRegex;
    QRegExp imageRegex;
    QRegExp inlineCodeRegex;
};

#endif // MARKDOWNHIGHLIGHTER_H
