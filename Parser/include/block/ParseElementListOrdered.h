#ifndef PARSE_ELEM_LIST_ORDERED_H
#define PARSE_ELEM_LIST_ORDERED_H

#include "ParseElementList.h"

class ParseElementListOrdered : public ParseElementList {
public:
    ParseElementListOrdered();
    virtual ~ParseElementListOrdered() = default;
    virtual ParseElementType type() const override final;

    virtual bool tryParse(const QString &line, int offset, int& length) override final;

protected:
    virtual QString getListOpenTag() const override final;
    virtual QString getListCloseTag() const override final;
};

#endif // PARSE_ELEM_LIST_ORDERED_H
