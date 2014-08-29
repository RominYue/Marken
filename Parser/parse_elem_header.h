#ifndef PARSE_ELEM_HEADER_H
#define PARSE_ELEM_HEADER_H

#include "parse_elem_block.h"

class ParseElementHeader : public ParseElementBlock {
public:
    ParseElementHeader();

    int level;

protected:
    string getCleanedHeader() const;
    string generateOpenTag() const;
    string generateCloseTag() const;
};

#endif // PARSE_ELEM_HEADER_H
