#ifndef PARSE_ELEM_IMAGE_H
#define PARSE_ELEM_IMAGE_H

#include "parse_elem_span.h"
#include "parse_elem_link.h"

class ParseElementImage : public ParseElementSpan, public ParseElementLink {
public:
    ParseElementImage();
    virtual ParseElementType type() const override final;
};

#endif // PARSE_ELEM_IMAGE_H
