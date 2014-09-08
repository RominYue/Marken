#ifndef PARSE_ELEM_CODE_INLINE_H
#define PARSE_ELEM_CODE_INLINE_H

#include "ParseElementSpan.h"

class ParseElementCodeInline : public ParseElementSpan {
public:
    ParseElementCodeInline();
    virtual ~ParseElementCodeInline() = default;
    virtual ParseElementType type() const override final;

    virtual qint32 tryParse(const QString& text, qint32 offset) override final;
    virtual QString generateOpenHtml() const override final;
    virtual QString generateCloseHtml() const override final;

private:
    qint32 _backtickNum;
};

#endif // PARSE_ELEM_CODE_INLINE_H
