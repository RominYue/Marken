#ifndef PARSE_ELEM_HEADER_H
#define PARSE_ELEM_HEADER_H

#include "ParseElementBlock.h"

class ParseElementHeader : public ParseElementBlock {
public:
    ParseElementHeader();
    virtual ~ParseElementHeader() = default;

    QString getCleanedHeader() const;
    int getCleanStartIndex() const;
    int getCleanEndIndex() const;

    int level;

protected:
    QString generateOpenTag() const;
    QString generateCloseTag() const;
};

#endif // PARSE_ELEM_HEADER_H
