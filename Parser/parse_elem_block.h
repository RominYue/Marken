#ifndef PARSE_ELEM_BLOCK_H_INCLUDED
#define PARSE_ELEM_BLOCK_H_INCLUDED

#include "parse_elem.h"

class ParseElemBlock : public ParseElem {
public:
    ParseElemBlock();
    virtual bool isBlockElement() const override final;

    virtual std::string generateOpenHtml() const;
    virtual std::string generateCloseHtml() const;
};

#endif // PARSE_ELEM_BLOCK_H_INCLUDED
