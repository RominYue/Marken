#ifndef PARSE_LINE_DATA_H_INCLUDED
#define PARSE_LINE_DATA_H_INCLUDED

#include <vector>
#include <string>
#include <memory>
#include "parse_elems.h"

class ParseLineData {
public:
    ParseLineData();
    virtual ~ParseLineData();

    std::vector<std::shared_ptr<ParseElem>>& elems();
    std::shared_ptr<ParseElem> operator [](const int index) const;
    std::string generateHtml() const;

    bool isChanged() const;
    void saveStruct();
private:
    std::vector<std::shared_ptr<ParseElem>> _elems;
    std::vector<std::shared_ptr<ParseElem>> _olds;
};

#endif // PARSE_LINE_DATA_H_INCLUDED
