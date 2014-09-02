#ifndef PARSE_ELEM_IMAGE_INLINE_H
#define PARSE_ELEM_IMAGE_INLINE_H

#include "parse_elem_image.h"

class ParseElementImageInline : public ParseElementImage{
public:
    ParseElementImageInline();
    virtual ParseElementType type() const override final;

    virtual int tryParse(const string& text, int offset) override final;
    virtual string generateOpenHtml() const override final;
};

#endif // PARSE_ELEM_IMAGE_INLINE_H
