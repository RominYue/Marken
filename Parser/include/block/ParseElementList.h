#ifndef PARSE_ELEM_LIST_H
#define PARSE_ELEM_LIST_H

#include "ParseElementBlock.h"

class ParseElementList : public ParseElementBlock {
public:
    ParseElementList();
    virtual ~ParseElementList() = default;

    virtual bool inheritable() const override final;
    virtual QString generateOpenHtml() const override final;
    virtual QString generateCloseHtml() const override final;

protected:
    virtual QString getListOpenTag() const;
    virtual QString getListCloseTag() const;
};

#endif // PARSE_ELEM_LIST_H
