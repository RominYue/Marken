#ifndef PARSE_ELEM_CODE_INLINE_H
#define PARSE_ELEM_CODE_INLINE_H

#include "parse_elem_span.h"

class ParseElementCodeInline : public ParseElementSpan {
public:
    ParseElementCodeInline();
    virtual ParseElementType type() const override final;

    virtual int tryParse(const string& text, int offset) override final;
    virtual string generateOpenHtml() const override final;
    virtual string generateCloseHtml() const override final;

private:
    int _backtickNum;
};

#endif // PARSE_ELEM_CODE_INLINE_H
