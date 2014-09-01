#ifndef PARSE_ELEM_HEADER_H
#define PARSE_ELEM_HEADER_H

#include "parse_elem_block.h"

class ParseElementHeader : public ParseElementBlock {
public:
    ParseElementHeader();

    string getCleanedHeader() const;
    int getCleanStartIndex() const;
    int getCleanEndIndex() const;

    int level;

protected:
    string generateOpenTag() const;
    string generateCloseTag() const;
};

#endif // PARSE_ELEM_HEADER_H
