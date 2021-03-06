#ifndef PARSE_ELEM_BLOCK_H
#define PARSE_ELEM_BLOCK_H

#include "parse_elem.h"

class ParseElementBlock : public ParseElement {
public:
    ParseElementBlock();
    virtual bool isBlockElement() const override final;

    virtual bool tryParse(const string &line, int offset, int& length);

    virtual bool nestable() const;
    virtual bool inheritable() const;

    bool isVirtual;
};

#endif // PARSE_ELEM_BLOCK_H
