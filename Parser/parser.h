#ifndef PARSER_H
#define PARSER_H

#include "parse_elems.h"
#include "parse_line_data.h"

class Parser {
public:
    Parser();
    virtual ~Parser();

    void parseLine(ParseLineData* data, std::string line);
    std::vector<std::string> parseToList(std::vector<std::string>& document);
    std::string parseToHtml(std::vector<std::string>& document);

private:
    std::vector<std::shared_ptr<ParseElemBlock>> _blockElems;
    std::vector<std::shared_ptr<ParseElemSpan>> _spanElems;

    std::vector<std::shared_ptr<ParseLineData>> parseToDataList(std::vector<std::string>& document);

    bool isUtf8FirstCharacter(const char ch) const;
};

#endif // PARSER_H
