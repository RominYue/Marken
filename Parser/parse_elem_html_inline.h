#ifndef PARSE_ELEM_HTML_INLINE_H
#define PARSE_ELEM_HTML_INLINE_H

#include "parse_elem_span.h"

class ParseElementHtmlInline : public ParseElementSpan {
public:
    ParseElementHtmlInline();
    virtual ParseElementType type() const override final;
};

#endif // PARSE_ELEM_HTML_INLINE_H
