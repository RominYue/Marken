#ifndef PARSE_ELEM_CODE_INLINE_H
#define PARSE_ELEM_CODE_INLINE_H

#include "parse_elem_span.h"

class ParseElementCodeInline : public ParseElementSpan {
public:
    ParseElementCodeInline();
    virtual ParseElementType type() const override final;
};

#endif // PARSE_ELEM_CODE_INLINE_H
