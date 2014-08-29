#ifndef PARSE_ELEM_CODE_BLOCK_H
#define PARSE_ELEM_CODE_BLOCK_H

#include "parse_elem_block.h"

class ParseElementCodeBlock : public ParseElementBlock {
public:
    ParseElementCodeBlock();
    virtual ParseElementType type() const override final;

    virtual bool tryParse(const string &line, int offset, int& length) override final;

    virtual string generateOpenHtml() const override final;
    virtual string generateCloseHtml() const override final;
};

#endif // PARSE_ELEM_CODE_BLOCK_H
