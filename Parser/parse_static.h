#ifndef PARSE_STATIC_H
#define PARSE_STATIC_H

#include <string>
#include <vector>
using std::string;
using std::vector;

class StaticParser {
public:
    StaticParser() = default;
    virtual ~StaticParser() = default;
    vector<string> parseToHtmlList(const vector<string>& document) const;
    string parseToHtml(const vector<string>& document) const;
};

#endif // PARSE_STATIC_H
