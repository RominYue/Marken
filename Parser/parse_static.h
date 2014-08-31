#ifndef PARSE_STATIC_H
#define PARSE_STATIC_H

#include <string>
#include <vector>
#include "parse.h"
using std::string;
using std::vector;

class StaticParser : public Parser {
public:
    StaticParser();
    vector<string> parseToHtmlList(const vector<string>& document) const;
    string parseToHtml(const vector<string>& document) const;
};

#endif // PARSE_STATIC_H
