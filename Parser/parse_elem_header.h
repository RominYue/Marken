#ifndef PARSE_ELEM_HEADER_H_INCLUDED
#define PARSE_ELEM_HEADER_H_INCLUDED

#include "parse_elem.h"

class ParseElemHeader : public ParseElem {
public:
    ParseElemHeader();
    int level() const;
    void setLevel(const int level);

    virtual std::string generateHtml() const override;

protected:
    int _level;

    std::string getCleanHeader() const;
    bool isRemovableCharacter(const char ch) const;
};


#endif // PARSE_ELEM_HEADER_H_INCLUDED
