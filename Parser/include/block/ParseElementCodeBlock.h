#ifndef PARSE_ELEM_CODE_BLOCK_H
#define PARSE_ELEM_CODE_BLOCK_H

#include "ParseElementBlock.h"

class ParseElementCodeBlock : public ParseElementBlock {
public:
    ParseElementCodeBlock();
    virtual ~ParseElementCodeBlock() = default;
    virtual ParseElementType type() const override final;

    virtual bool inheritable() const override final;
    virtual bool tryParse(const QString &line, int offset, int& length) override final;

    virtual QString generateOpenHtml() const override final;
    virtual QString generateCloseHtml() const override final;

private:
    bool _isEmpty;
};

#endif // PARSE_ELEM_CODE_BLOCK_H
