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
    vector<string> parseToHtmlList(const string& filePath) const;
    string parseToHtml(const string& filePath) const;
    void parseToFile(const string& srcPath, const string& tarPath) const;

private:
    void readDocument(const string& filePath, vector<string>& document) const;
    void saveDocument(const string& filePath, vector<string>& document) const;
};

#endif // PARSE_STATIC_H
