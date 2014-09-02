#ifndef PARSE_ELEM_LINK_REFERENCE_H
#define PARSE_ELEM_LINK_REFERENCE_H

#include "parse_elem_span.h"
#include "parse_elem_link.h"

class ParseElementLinkReference : public ParseElementSpan, public ParseElementLink {
public:
    ParseElementLinkReference();
    virtual ParseElementType type() const override final;

    virtual int tryParse(const string& text, int offset) override final;
    virtual string generateOpenHtml() const override final;
    virtual string generateCloseHtml() const override final;

    virtual void remove() override final;

private:
    string _inner;
    string _label;
};

#endif // PARSE_ELEM_LINK_REFERENCE_H
