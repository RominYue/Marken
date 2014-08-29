#ifndef PARSE_ELEM_LIST_ORDERED_H
#define PARSE_ELEM_LIST_ORDERED_H

#include "parse_elem_list.h"

class ParseElementListOrdered : public ParseElementList {
public:
    ParseElementListOrdered();
    virtual ParseElementType type() const override final;

    virtual bool tryParse(const string &line, int offset, int& length) override final;

protected:
    virtual string getListOpenTag() const override final;
    virtual string getListCloseTag() const override final;
};

#endif // PARSE_ELEM_LIST_ORDERED_H
