#ifndef PARSE_ELEM_STRONG_H
#define PARSE_ELEM_STRONG_H

#include "ParseElementSpan.h"

class ParseElementStrong : public ParseElementSpan {
public:
    ParseElementStrong();
    virtual ~ParseElementStrong() = default;
    virtual ParseElementType type() const override final;

    virtual int tryParse(const QString& text, int offset) override final;
    virtual QString generateOpenHtml() const override final;
    virtual QString generateCloseHtml() const override final;

    virtual QString innerText() const override final;
    virtual int innerOffset() const override final;
};

#endif // PARSE_ELEM_STRONG_H
