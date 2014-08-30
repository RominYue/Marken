#ifndef PARSE_ELEM_QUOTE_H
#define PARSE_ELEM_QUOTE_H

#include "parse_elem_block.h"

class ParseElementQuote : public ParseElementBlock {
public:
    ParseElementQuote();
    virtual ParseElementType type() const;

    virtual bool tryParse(const string &line, int offset, int& length) override final;

    virtual bool inheritable() const override final;
    virtual string generateOpenHtml() const override final;
    virtual string generateCloseHtml() const override final;
};

#endif // PARSE_ELEM_QUOTE_H
