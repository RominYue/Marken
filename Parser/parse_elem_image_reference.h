#ifndef PARSE_ELEM_IMAGE_REFERENCE_H
#define PARSE_ELEM_IMAGE_REFERENCE_H

#include "parse_elem_image.h"

class ParseElementImageReference : public ParseElementImage{
public:
    ParseElementImageReference();
    virtual ParseElementType type() const override final;

    virtual int tryParse(const string& text, int offset) override final;
    virtual string generateOpenHtml() const override final;

private:
    string _label;
};

#endif // PARSE_ELEM_IMAGE_REFERENCE_H
