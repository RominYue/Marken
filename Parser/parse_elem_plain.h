#ifndef PARSE_ELEM_PLAIN_H
#define PARSE_ELEM_PLAIN_H

#include "parse_elem_span.h"

class ParseElementPlain : public ParseElementSpan {
public:
    ParseElementPlain();
    virtual ParseElementType type() const override final;

    virtual string generateOpenHtml() const override final;
};

#endif // PARSE_ELEM_PLAIN_H
