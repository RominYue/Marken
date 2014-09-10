#ifndef PARSE_ELEM_LINK_AUTOMATIC_H
#define PARSE_ELEM_LINK_AUTOMATIC_H

#include "ParseElementSpan.h"
#include "ParseElementLink.h"

class ParseElementLinkAutomatic : public ParseElementSpan, public ParseElementLink {
public:
    ParseElementLinkAutomatic();
    virtual ~ParseElementLinkAutomatic() = default;
    virtual ParseElementType type() const override final;

    virtual int tryParse(const QString& text, int offset) override final;
    virtual QString generateOpenHtml() const override final;

private:
    QString _link;

    bool isLink() const;
    bool isEmail() const;

    QString htmlEscaped(const QString& text) const;
};

#endif // PARSE_ELEM_LINK_AUTOMATIC_H
