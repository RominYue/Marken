#ifndef PARSE_ELEM_TEXT_H_INCLUDED
#define PARSE_ELEM_TEXT_H_INCLUDED

#include "parse_elem_span.h"

class ParseElemText : public ParseElemSpan {
public:
    ParseElemText();
    virtual ParseElemType type() const override final;

    std::string generateHtml() const override final;

private:
    enum AmpersandStatus {
        STATUS_AMP,
        STATUS_HASH,
        STATUS_ALPHA,
        STATUS_DIGIT,
        STATUS_ACCEPT,
        STATUS_FAILED,
    };
};

#endif // PARSE_ELEM_TEXT_H_INCLUDED
