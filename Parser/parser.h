#ifndef PARSER_H
#define PARSER_H

#include <vector>
#include <string>

class Parser {
public:
    Parser();
    virtual ~Parser();

    std::vector<std::string> parseToList(std::vector<std::string>& document);
    std::string parseToHtml(std::vector<std::string>& document);
};

#endif // PARSER_H
