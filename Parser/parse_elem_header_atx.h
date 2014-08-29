#ifndef PARSE_ELEM_HEADER_ATX_H
#define PARSE_ELEM_HEADER_ATX_H

#include "parse_elem_header.h"

class ParseElementHeaderAtx : public ParseElementHeader {
public:
    ParseElementHeaderAtx();
    virtual ParseElementType type() const override final;

    virtual bool tryParse(const string &line, int offset, int& length) override final;

    virtual string generateOpenHtml() const override final;
    virtual string generateCloseHtml() const override final;
};

#endif // PARSE_ELEM_HEADER_ATX_H
