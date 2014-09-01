#ifndef PARSE_ELEM_LINK_REFERENCE_H
#define PARSE_ELEM_LINK_REFERENCE_H

#include "parse_elem_link.h"

class ParseElementLinkReference : public ParseElementLink {
public:
    ParseElementLinkReference();
    virtual ParseElementType type() const override final;
};

#endif // PARSE_ELEM_LINK_REFERENCE_H
