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
    virtual string inlineText() const;
    virtual bool operator ==(shared_ptr<ParseElement> element) const;

    virtual string generateOpenHtml() const;
    virtual string generateCloseHtml() const;

    int offset;
    int inlineOffset;
    int utf8Offset;
    int utf8Length;
    string text;
    ParseLine* parent;

protected:
    string translateAmp(const string& text) const;
};

#endif // PARSE_ELEM_H_INCLUDED
