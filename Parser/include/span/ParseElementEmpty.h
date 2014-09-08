#ifndef PARSE_ELEM_EMPTY_H
#define PARSE_ELEM_EMPTY_H

#include "ParseElementBlock.h"

class ParseElementEmpty : public ParseElementBlock {
public:
    ParseElementEmpty();
    virtual ~ParseElementEmpty() = default;
    virtual ParseElementType type() const override final;
};

#endif // PARSE_ELEM_EMPTY_H
