#ifndef PARSE_ELEM_IMAGE_INLINE_H
#define PARSE_ELEM_IMAGE_INLINE_H

#include "ParseElementImage.h"

class ParseElementImageInline : public ParseElementImage{
public:
    ParseElementImageInline();
    virtual ~ParseElementImageInline() = default;
    virtual ParseElementType type() const override final;

    virtual qint32 tryParse(const QString& text, qint32 offset) override final;
    virtual QString generateOpenHtml() const override final;
};

#endif // PARSE_ELEM_IMAGE_INLINE_H
