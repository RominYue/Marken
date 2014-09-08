#ifndef PARSE_ELEM_HEADER_H
#define PARSE_ELEM_HEADER_H

#include "ParseElementBlock.h"

class ParseElementHeader : public ParseElementBlock {
public:
    ParseElementHeader();
    virtual ~ParseElementHeader() = default;

    QString getCleanedHeader() const;
    qint32 getCleanStartIndex() const;
    qint32 getCleanEndIndex() const;

    qint32 level;

protected:
    QString generateOpenTag() const;
    QString generateCloseTag() const;
};

#endif // PARSE_ELEM_HEADER_H
