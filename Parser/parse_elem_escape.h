#ifndef PARSE_ELEM_ESCAPE_H
#define PARSE_ELEM_ESCAPE_H

#include "parse_elem_span.h"

class ParseElementEscape : public ParseElementSpan {
public:
    ParseElementEscape();
    virtual int tryParse(const string& text, int offset) override final;
    virtual string generateHtml() const override final;
};

#endif // PARSE_ELEM_ESCAPE_H
