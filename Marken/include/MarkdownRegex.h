#ifndef MARKDOWNREGEX_H
#define MARKDOWNREGEX_H

#include <QMap>
#include <QRegExp>
#include "MarkdownDefination.h"

class MarkdownRegex {
public:
    MarkdownRegex();
    const QMap<MarkdownDefination::SyntaxType, QRegExp>& regex() const;
    const QRegExp& regex(MarkdownDefination::SyntaxType name) const;
    const QRegExp& empty() const;

private:
    QRegExp _matchEmpty;
    QMap<MarkdownDefination::SyntaxType, QRegExp> _regex;

    void initRegex();
};

#endif // MARKDOWNREGEX_H
