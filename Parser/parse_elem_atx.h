#ifndef PARSE_ELEM_ATX_H_INCLUDED
#define PARSE_ELEM_ATX_H_INCLUDED

#include "parse_elem_header.h"

class ParseElemAtx : public ParseElemHeader {
public:
    ParseElemAtx();
    virtual ParseElemType type() const override final;
};

#endif // PARSE_ELEM_ATX_H_INCLUDED
