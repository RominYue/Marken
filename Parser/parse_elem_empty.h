#ifndef PARSE_ELEM_EMPTY_H
#define PARSE_ELEM_EMPTY_H

#include "parse_elem_block.h"

class ParseElementEmpty : public ParseElementBlock {
public:
    ParseElementEmpty();
    virtual ParseElementType type() const override final;
};

#endif // PARSE_ELEM_EMPTY_H
