#ifndef PARSE_ELEM_EMPHASIS_H
#define PARSE_ELEM_EMPHASIS_H

#include "ParseElementSpan.h"

class ParseElementEmphasis : public ParseElementSpan {
public:
    ParseElementEmphasis();
    virtual ~ParseElementEmphasis() = default;
    virtual ParseElementType type() const override final;

    virtual qint32 tryParse(const QString& text, qint32 offset) override final;
    virtual QString generateOpenHtml() const override final;
    virtual QString generateCloseHtml() const override final;

    virtual QString innerText() const override final;
    virtual qint32 innerOffset() const override final;
};

#endif // PARSE_ELEM_EMPHASIS_H
