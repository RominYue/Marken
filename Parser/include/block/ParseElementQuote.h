#ifndef PARSE_ELEM_QUOTE_H
#define PARSE_ELEM_QUOTE_H

#include "ParseElementBlock.h"

class ParseElementQuote : public ParseElementBlock {
public:
    ParseElementQuote();
    virtual ~ParseElementQuote() = default;
    virtual ParseElementType type() const;

    virtual bool tryParse(const QString &line, int offset, int& length) override final;

    virtual bool inheritable() const override final;
    virtual QString generateOpenHtml() const override final;
    virtual QString generateCloseHtml() const override final;
};

#endif // PARSE_ELEM_QUOTE_H
