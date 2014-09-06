#ifndef PARSE_ELEM_ESCAPE_H
#define PARSE_ELEM_ESCAPE_H

#include "parse_elem_span.h"

class ParseElementEscape : public ParseElementSpan {
public:
    ParseElementEscape();
    virtual ParseElementType type() const override final;

    virtual int tryParse(const string& text, int offset) override final;
    virtual string generateOpenHtml() const override final;

private:
    char _escaped;
};

#endif // PARSE_ELEM_ESCAPE_H
