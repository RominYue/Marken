#ifndef MARKDOWNPARSER_H
#define MARKDOWNPARSER_H

#include <QMap>
#include <QString>
#include <QTextDocument>
#include "MarkdownBlockData.h"

class MarkdownParser {
public:
    MarkdownParser();
    QString generateHtml(QTextDocument *document);

private:
    QMap<QString, QString> _links;
    QMap<QString, QString> _titles;

    MarkdownBlockData::LineType prevType(QTextBlock& block, int index) const;
    MarkdownBlockData::LineType nextType(QTextBlock& block, int index) const;

    QString removeCodeIndent(const QString &str);
    QString translate(const QString &str);
    QString removeSpaces(const QString &str);
    QString removeTitleHash(const QString &str);
    QString translateSpan(const QString &str);

    QString parseImage(const QString &str, int offset, int &length);
    QString parseLink(const QString &str, int offset, int &length);
    QString parseCode(const QString &str, int offset, int &length);
    QString parseHtml(const QString &str, int offset, int &length);
    QString parseEmphasis(const QString &str, int offset, int &length);
    QString parseTransChar(const QString &str, int offset, int &length);

    void findLinkLabels(QTextDocument *document);
};

#endif // MARKDOWNPARSER_H
