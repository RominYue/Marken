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
    bool parseOpenClose(const QString& text, int& index, QString& inner, QChar open, QChar close);
    bool parseBrackets(const QString& text, int& index, QString& inner);
    bool parseParentheses(const QString& text, int& index, QString& inner);
    bool parseLink(const QString& text, int& index, QString& link);
    bool parseTitle(const QString& text, int& index, QString& title);

    QString generateOpenLinkHtml(const QString& href, const QString& title) const;
};

#endif // PARSE_ELEM_LINKS_H
