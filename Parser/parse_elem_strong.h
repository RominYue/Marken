#ifndef PARSE_ELEM_STRONG_H
#define PARSE_ELEM_STRONG_H

#include "parse_elem_span.h"

class ParseElementStrong : public ParseElementSpan {
public:
    ParseElementStrong();
    virtual ParseElementType type() const override final;

    virtual int tryParse(const string& text, int offset) override final;
    virtual string generateOpenHtml() const override final;
    virtual string generateCloseHtml() const override final;

    virtual string innerText() const override final;
    virtual int innerOffset() const override final;
};

#endif // PARSE_ELEM_STRONG_H
