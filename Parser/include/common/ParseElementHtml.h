#ifndef PARSE_ELEM_HTML_H
#define PARSE_ELEM_HTML_H

#include <QString>

class ParseElementHtml {
public:
    ParseElementHtml();
    virtual ~ParseElementHtml() = default;

    const QString& tag() const;
    void setTag(const QString& val);

protected:
    enum Status {
        STATUS_BEGIN,
        STATUS_LT,
        STATUS_SLASH,
        STATUS_TAG,
        STATUS_SPACE_SUF,
        STATUS_ATTRIBUTE,
        STATUS_STRING,
        STATUS_ESCAPE,
        STATUS_GT
    };
    QString _tag;
    bool findOpenTagOffset(const QString &line, int &index);
    bool findCloseTagOffset(const QString &line, int &index);
    bool matchToTagEnd(const QString &line, int &index);
    bool matchToGt(const QString &line, int &index);
    bool matchToEnd(const QString &line, int &index);
};

#endif // PARSE_ELEM_HTML_H
