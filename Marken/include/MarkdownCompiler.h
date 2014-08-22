#ifndef MARKDOWNCOMPILER_H
#define MARKDOWNCOMPILER_H

#include <QList>
#include <QStringList>
#include "MarkdownDefination.h"
#include "MarkdownRegex.h"

class MarkdownCompiler {
public:
    MarkdownCompiler();
    void analysis(const QStringList &list);
    QString parseToHTML(const QStringList &list);

private:
    enum Status {
        STATUS_DEFAULT,
        STATUS_ATX_HEADER,
    };
    enum LineType {
        LINE_DEFAULT,
        LINE_EMPTY,
        LINE_ATX_HEADER_1,
        LINE_ATX_HEADER_2,
        LINE_ATX_HEADER_3,
        LINE_ATX_HEADER_4,
        LINE_ATX_HEADER_5,
        LINE_ATX_HEADER_6,
        LINE_SETEXT_HEADER_1,
        LINE_SETEXT_HEADER_2,
        LINE_BLOCK_QUOTE,
        LINE_UNORDERED_LIST,
        LINE_ORDERED_LIST,
        LINE_CODE_BLOCK,
        LINE_HORIZONTAL,
        LINE_LINK_LABEL,
    };
    QList<LineType> _types;
    MarkdownRegex _regex;

    QString cleanHeader(const QString& header) const;
    int findNext(const QString &str, char ch, int index = 0) const;
    QString getLink(const QString &str) const;
    QString translate(const QString& str) const;
};

#endif // MARKDOWNCOMPILER_H
