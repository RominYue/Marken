#ifndef PARSE_ELEM_LINK_INLINE_H
#define PARSE_ELEM_LINK_INLINE_H

#include "parse_elem_span.h"
#include "parse_elem_link.h"

class ParseElementLinkInline : public ParseElementSpan, public ParseElementLink {
public:
    ParseElementLinkInline();
    virtual ParseElementType type() const override final;

    virtual int tryParse(const string& text, int offset) override final;
    virtual string generateOpenHtml() const override final;
    virtual string generateCloseHtml() const override final;

    virtual string innerText() const override final;
    virtual int innerOffset() const override final;

private:
    string _inner;
    string _help;
    string _link;
    string _title;
};

#endif // PARSE_ELEM_LINK_INLINE_H
