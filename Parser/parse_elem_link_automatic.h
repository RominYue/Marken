#ifndef PARSE_ELEM_LINK_AUTOMATIC_H
#define PARSE_ELEM_LINK_AUTOMATIC_H

#include "parse_elem_span.h"
#include "parse_elem_link.h"

class ParseElementLinkAutomatic : public ParseElementSpan, public ParseElementLink {
public:
    ParseElementLinkAutomatic();
    virtual ParseElementType type() const override final;

    virtual int tryParse(const string& text, int offset) override final;
    virtual string generateOpenHtml() const override final;

private:
    string _link;

    bool isLink() const;
    bool isEmail() const;

    string translateToAmp(const string& text) const;
};

#endif // PARSE_ELEM_LINK_AUTOMATIC_H
