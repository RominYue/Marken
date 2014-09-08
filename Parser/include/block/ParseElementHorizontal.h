#ifndef PARSE_ELEM_HORIZONTAL_H
#define PARSE_ELEM_HORIZONTAL_H

#include "ParseElementBlock.h"

class ParseElementHorizontal : public ParseElementBlock {
public:
    ParseElementHorizontal();
    virtual ~ParseElementHorizontal() = default;
    virtual ParseElementType type() const override final;

    virtual bool tryParse(const QString &line, qint32 offset, qint32& length) override final;

    virtual QString generateOpenHtml() const override final;
    virtual QString generateCloseHtml() const override final;
};

#endif // PARSE_ELEM_HORIZONTAL_H
