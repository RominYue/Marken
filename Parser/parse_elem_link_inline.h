#ifndef PARSE_ELEM_LINK_INLINE_H
#define PARSE_ELEM_LINK_INLINE_H

#include "parse_elem_link.h"

class ParseElementLinkInline : public ParseElementLink {
public:
    ParseElementLinkInline();
    virtual ParseElementType type() const override final;
};

#endif // PARSE_ELEM_LINK_INLINE_H
