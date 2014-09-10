#ifndef PARSE_ELEM_HEADER_SETEXT_H
#define PARSE_ELEM_HEADER_SETEXT_H

#include "ParseElementHeader.h"

class ParseElementHeaderSetext : public ParseElementHeader {
public:
    ParseElementHeaderSetext();
    virtual ~ParseElementHeaderSetext() = default;
    virtual ParseElementType type() const override final;

    virtual bool tryParse(const QString &line, int offset, int& length) override final;

    virtual QString generateOpenHtml() const override final;
    virtual QString generateCloseHtml() const override final;

    bool isLower() const;

private:
    bool _isLower;
};

#endif // PARSE_ELEM_HEADER_SETEXT_H
