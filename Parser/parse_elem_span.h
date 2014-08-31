#ifndef PARSE_ELEM_SPAN_H
#define PARSE_ELEM_SPAN_H

#include "parse_elem.h"

class ParseElementSpan : public ParseElement {
public:
    ParseElementSpan();
    virtual bool isBlockElement() const override final;

    virtual int tryParse(const string& text, int offset);
    virtual string generateHtml() const;

    int length;
};

#endif // PARSE_ELEM_SPAN_H
