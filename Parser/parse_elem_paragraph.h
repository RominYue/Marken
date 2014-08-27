#ifndef PARSE_ELEM_PARAGRAPH_H_INCLUDED
#define PARSE_ELEM_PARAGRAPH_H_INCLUDED

#include "parse_elem_block.h"

class ParseElemParagraph : public ParseElemBlock {
public:
    ParseElemParagraph();

    virtual ParseElemType type() const override final;
    virtual bool tryParse(std::string text, int offset, int &len) override final;

    virtual std::string generateOpenHtml() const override final;
    virtual std::string generateCloseHtml() const override final;
};

#endif // PARSE_ELEM_PARAGRAPH_H_INCLUDED
