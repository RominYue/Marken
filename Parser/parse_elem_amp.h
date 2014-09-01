#ifndef PARSE_ELEM_AMP_H
#define PARSE_ELEM_AMP_H

#include "parse_elem_span.h"

class ParseElementAmp : public ParseElementSpan {
public:
    ParseElementAmp();
    virtual ParseElementType type() const override final;

    virtual int tryParse(const string& text, int offset) override final;
    virtual string generateOpenHtml() const override final;

private:
    enum Status {
        STATUS_AMP,
        STATUS_ALPHA,
        STATUS_HASH,
        STATUS_DIGIT,
        STATUS_DELIMITER
    };
};

#endif // PARSE_ELEM_AMP_H
