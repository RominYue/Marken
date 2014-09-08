#ifndef PARSE_ELEM_LINKS_H
#define PARSE_ELEM_LINKS_H

#include <QString>

class ParseElementLink {
public:
    ParseElementLink();
    virtual ~ParseElementLink() = default;

protected:
    enum Status {
        STATUS_BEGIN,
        STATUS_LEFT,
        STATUS_TEXT,
        STATUS_ESCAPE,
        STATUS_RIGHT,
    };
    bool ParserOpenClose(const QString& text, qint32& index, QString& inner, QChar open, QChar close);
    bool ParserBrackets(const QString& text, qint32& index, QString& inner);
    bool ParserParentheses(const QString& text, qint32& index, QString& inner);

    QString getCleanedLink(const QString& link) const;
    QString getCleanedTitle(const QString& title) const;
    QString getCleanedLabel(const QString& label) const;

    QString generateOpenLinkHtml(const QString& href, const QString& title) const;
};

#endif // PARSE_ELEM_LINKS_H
