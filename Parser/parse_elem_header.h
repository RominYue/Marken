#ifndef PARSE_ELEM_HEADER_H_INCLUDED
#define PARSE_ELEM_HEADER_H_INCLUDED

#include "parse_elem_block.h"

class ParseElemHeader : public ParseElemBlock {
public:
    ParseElemHeader();
    int level() const;
    void setLevel(const int level);

    virtual std::string generateOpenHtml() const override;
    virtual std::string generateCloseHtml() const override;

protected:
    int _level;

    std::string getCleanHeader() const;
    bool isRemovableCharacter(const char ch) const;
};


#endif // PARSE_ELEM_HEADER_H_INCLUDED
