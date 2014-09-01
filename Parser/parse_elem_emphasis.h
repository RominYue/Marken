#ifndef PARSE_ELEM_EMPHASIS_H
#define PARSE_ELEM_EMPHASIS_H

#include "parse_elem_span.h"

class ParseElementEmphasis : public ParseElementSpan {
public:
    ParseElementEmphasis();
    virtual ParseElementType type() const override final;
};

#endif // PARSE_ELEM_EMPHASIS_H
