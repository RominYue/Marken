#ifndef PARSE_ELEM_BLOCK_H
#define PARSE_ELEM_BLOCK_H

#include "ParseElement.h"

class ParseElementBlock : public ParseElement {
public:
    ParseElementBlock();
    virtual ~ParseElementBlock() = default;
    virtual bool isBlockElement() const override final;

    virtual bool stopParsing(qint32 offset) const;
    virtual bool tryParse(const QString &line, qint32 offset, qint32& length);

    virtual bool inheritable() const;

    bool isVirtual;
};

#endif // PARSE_ELEM_BLOCK_H
