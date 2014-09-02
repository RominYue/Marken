#ifndef PARSE_ELEM_SPAN_H
#define PARSE_ELEM_SPAN_H

#include "parse_elem.h"

class ParseElementSpan : public ParseElement {
public:
    ParseElementSpan();
    virtual bool isBlockElement() const override final;

    virtual int tryParse(const string& text, int offset);

    bool openActivate;
    bool closeActivate;
};

#endif // PARSE_ELEM_SPAN_H
