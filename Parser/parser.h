#ifndef PARSER_H
#define PARSER_H

#include "parse_line_data.h"

class Parser {
public:
    Parser();
    virtual ~Parser();

    std::shared_ptr<ParseLineData> parseLine(std::shared_ptr<ParseLineData> data, std::string line);
    std::vector<std::string> parseToList(std::vector<std::string>& document);
    std::string parseToHtml(std::vector<std::string>& document);

private:
    std::vector<std::shared_ptr<ParseLineData>> parseToDataList(std::vector<std::string>& document);
};

#endif // PARSER_H
