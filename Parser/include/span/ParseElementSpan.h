#ifndef PARSE_ELEM_SPAN_H
#define PARSE_ELEM_SPAN_H

#include "ParseElement.h"

class ParseElementSpan : public ParseElement {
public:
    ParseElementSpan();
    virtual ~ParseElementSpan() = default;
    virtual bool isBlockElement() const override final;

    virtual int tryParse(const QString& text, int offset);

    bool openActivate;
    bool closeActivate;
};

#endif // PARSE_ELEM_SPAN_H
