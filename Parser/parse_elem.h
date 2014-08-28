#ifndef PARSE_ELEM_H_INCLUDED
#define PARSE_ELEM_H_INCLUDED

#include <string>
#include <memory>
#include "parse_elem_type.h"
using std::string;
using std::shared_ptr;

class ParseLine;

class ParseElement {
public:
    ParseElement();

    virtual ParseElementType type() const;
    virtual bool isBlockElement() const;
    virtual bool operator ==(shared_ptr<ParseElement> element) const;

    int offset;
    int utf8Offset;
    int utf8Length;
    string text;
    ParseLine* parent;
};

#endif // PARSE_ELEM_H_INCLUDED
