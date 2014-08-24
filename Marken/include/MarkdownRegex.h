#ifndef MARKDOWNREGEX_H
#define MARKDOWNREGEX_H

#include <QMap>
#include <QRegExp>
#include "MarkdownDefine.h"

class MarkdownRegex {
public:
    MarkdownRegex();
    const QMap<MarkdownDefine::SyntaxType, QRegExp>& regex() const;
    const QRegExp& regex(MarkdownDefine::SyntaxType name) const;
    const QRegExp& empty() const;

private:
    QRegExp _matchEmpty;
    QMap<MarkdownDefine::SyntaxType, QRegExp> _regex;

    void initRegex();
};

#endif // MARKDOWNREGEX_H
