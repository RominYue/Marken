#ifndef PARSE_ELEM_IMAGE_H
#define PARSE_ELEM_IMAGE_H

#include "parse_elem_span.h"
#include "parse_elem_link.h"

class ParseElementImage : public ParseElementSpan, public ParseElementLink {
public:
    ParseElementImage();

protected:
    string _alt;
    string _help;
    string _link;
    string _title;

    string generateOpenImageHtml(const string& link, const string& alt, const string& title) const;
};

#endif // PARSE_ELEM_IMAGE_H
