#ifndef PARSE_ELEM_HEADER_ATX_H
#define PARSE_ELEM_HEADER_ATX_H

#include "ParseElementHeader.h"

class ParseElementHeaderAtx : public ParseElementHeader {
public:
    ParseElementHeaderAtx();
    virtual ~ParseElementHeaderAtx() = default;
    virtual ParseElementType type() const override final;

    virtual bool tryParse(const QString &line, int offset, int& length) override final;

    virtual QString generateOpenHtml() const override final;
    virtual QString generateCloseHtml() const override final;
};

#endif // PARSE_ELEM_HEADER_ATX_H
