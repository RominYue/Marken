#ifndef PARSE_ELEM_HTML_INLINE_H
#define PARSE_ELEM_HTML_INLINE_H

#include "parse_elem_html.h"
#include "parse_elem_span.h"

class ParseElementHtmlInline : public ParseElementSpan, public ParseElementHtml {
public:
    ParseElementHtmlInline();
    virtual ParseElementType type() const override final;

    virtual int tryParse(const string& text, int offset) override final;
    virtual string generateOpenHtml() const override final;
};

#endif // PARSE_ELEM_HTML_INLINE_H
