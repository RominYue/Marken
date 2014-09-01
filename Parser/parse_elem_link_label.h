#ifndef PARSE_ELEM_LINK_LABEL_H
#define PARSE_ELEM_LINK_LABEL_H

#include "parse_elem_link.h"

class ParseElementLinkLabel : public ParseElementLink {
public:
    ParseElementLinkLabel();
    virtual ParseElementType type() const override final;
};

#endif // PARSE_ELEM_LINK_LABEL_H
