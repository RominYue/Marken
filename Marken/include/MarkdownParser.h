#ifndef MARKDOWNPARSER_H
#define MARKDOWNPARSER_H

#include <QString>
#include <QVector>
#include "MarkdownBlockData.h"

class MarkdownParser {
public:
    MarkdownParser();
    QString generateHtml(QTextBlock block);

private:
    MarkdownBlockData::LineType prevType(QTextBlock& block, int index) const;
    MarkdownBlockData::LineType nextType(QTextBlock& block, int index) const;

    QString removeCodeIndent(const QString &str);
    QString translate(const QString &str);
    QString removeTitleHash(const QString &str);
    QString translateSpan(const QString &str);

    QString parseImage(const QString &str, int offset, int &length);
    QString parseLink(const QString &str, int offset, int &length);
    QString parseCode(const QString &str, int offset, int &length);
    QString parseHtml(const QString &str, int offset, int &length);
    QString parseEmphasis(const QString &str, int offset, int &length);
    QString parseTransChar(const QString &str, int offset, int &length);
};

#endif // MARKDOWNPARSER_H
