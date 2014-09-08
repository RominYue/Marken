#ifndef PARSE_ELEM_AMP_H
#define PARSE_ELEM_AMP_H

#include "ParseElementSpan.h"

class ParseElementAmp : public ParseElementSpan {
public:
    ParseElementAmp();
    virtual ~ParseElementAmp() = default;
    virtual ParseElementType type() const override final;

    virtual qint32 tryParse(const QString& text, qint32 offset) override final;
    virtual QString generateOpenHtml() const override final;

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
