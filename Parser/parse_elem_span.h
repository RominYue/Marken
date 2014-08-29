#ifndef PARSE_ELEM_SPAN_H
#define PARSE_ELEM_SPAN_H

#include "parse_elem.h"

class Parseblockspan : public ParseElement {
public:
    Parseblockspan();
    virtual bool isBlockElement() const override final;

    virtual string generateHtml() const;

    bool activate;
};

#endif // PARSE_ELEM_SPAN_H
