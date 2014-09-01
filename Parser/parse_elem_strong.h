#ifndef PARSE_ELEM_STRONG_H
#define PARSE_ELEM_STRONG_H

#include "parse_elem_span.h"

class ParseElementStrong : public ParseElementSpan {
public:
    ParseElementStrong();
    virtual ParseElementType type() const override final;
};

#endif // PARSE_ELEM_STRONG_H
