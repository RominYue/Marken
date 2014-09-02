#ifndef PARSE_ELEM_HEADER_SETEXT_H
#define PARSE_ELEM_HEADER_SETEXT_H

#include "parse_elem_header.h"

class ParseElementHeaderSetext : public ParseElementHeader {
public:
    ParseElementHeaderSetext();
    virtual ParseElementType type() const override final;

    virtual bool tryParse(const string &line, int offset, int& length) override final;

    virtual string generateOpenHtml() const override final;
    virtual string generateCloseHtml() const override final;

    bool isLower() const;

private:
    bool _isLower;
};

#endif // PARSE_ELEM_HEADER_SETEXT_H
