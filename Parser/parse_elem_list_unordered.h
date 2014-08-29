#ifndef PARSE_ELEM_LIST_UNORDERED_H
#define PARSE_ELEM_LIST_UNORDERED_H

#include "parse_elem_list.h"

class ParseElementListUnordered : public ParseElementList {
public:
    ParseElementListUnordered();
    virtual ParseElementType type() const override final;

    virtual bool tryParse(const string &line, int offset, int& length) override final;

protected:
    virtual string getListOpenTag() const override final;
    virtual string getListCloseTag() const override final;
};

#endif // PARSE_ELEM_LIST_UNORDERED_H
