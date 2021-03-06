#ifndef PARSE_ELEM_HORIZONTAL_H
#define PARSE_ELEM_HORIZONTAL_H

#include "parse_elem_block.h"

class ParseElementHorizontal : public ParseElementBlock {
public:
    ParseElementHorizontal();
    virtual ParseElementType type() const override final;

    virtual bool tryParse(const string &line, int offset, int& length) override final;

    virtual string generateOpenHtml() const override final;
    virtual string generateCloseHtml() const override final;
};

#endif // PARSE_ELEM_HORIZONTAL_H
