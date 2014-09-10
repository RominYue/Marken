#ifndef PARSE_ELEM_LIST_UNORDERED_H
#define PARSE_ELEM_LIST_UNORDERED_H

#include "ParseElementList.h"

class ParseElementListUnordered : public ParseElementList {
public:
    ParseElementListUnordered();
    virtual ~ParseElementListUnordered() = default;
    virtual ParseElementType type() const override final;

    virtual bool tryParse(const QString &line, int offset, int& length) override final;

protected:
    virtual QString getListOpenTag() const override final;
    virtual QString getListCloseTag() const override final;
};

#endif // PARSE_ELEM_LIST_UNORDERED_H
