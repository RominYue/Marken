#ifndef PARSE_ELEM_PLAIN_H
#define PARSE_ELEM_PLAIN_H

#include "ParseElementSpan.h"

class ParseElementPlain : public ParseElementSpan {
public:
    ParseElementPlain();
    virtual ~ParseElementPlain() = default;
    virtual ParseElementType type() const override final;

    virtual QString generateOpenHtml() const override final;
};

#endif // PARSE_ELEM_PLAIN_H
