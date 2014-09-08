#ifndef PARSE_ELEM_ESCAPE_H
#define PARSE_ELEM_ESCAPE_H

#include "ParseElementSpan.h"

class ParseElementEscape : public ParseElementSpan {
public:
    ParseElementEscape();
    virtual ~ParseElementEscape() = default;
    virtual ParseElementType type() const override final;

    virtual qint32 tryParse(const QString& text, qint32 offset) override final;
    virtual QString generateOpenHtml() const override final;

private:
    QChar _escaped;
};

#endif // PARSE_ELEM_ESCAPE_H
