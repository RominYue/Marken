#ifndef PARSE_ELEM_LIST_H
#define PARSE_ELEM_LIST_H

#include "parse_elem_block.h"

class ParseElementList : public ParseElementBlock {
public:
    ParseElementList();

    virtual string generateOpenHtml() const override final;
    virtual string generateCloseHtml() const override final;

protected:
    virtual string getListOpenTag() const;
    virtual string getListCloseTag() const;
};

#endif // PARSE_ELEM_LIST_H
