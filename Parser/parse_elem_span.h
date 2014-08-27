#ifndef PARSE_ELEM_SPAN_H_INCLUDED
#define PARSE_ELEM_SPAN_H_INCLUDED

#include "parse_elem.h"

class ParseElemSpan : public ParseElem {
public:
    ParseElemSpan();
    virtual bool isBlockElement() const override final;

    virtual std::string generateHtml() const;
};

#endif // PARSE_ELEM_SPAN_H_INCLUDED
