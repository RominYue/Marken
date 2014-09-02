#ifndef PARSE_H
#define PARSE_H

#include <vector>
#include <string>
using std::vector;
using std::string;

class Parser {
public:
    Parser();
    virtual ~Parser();

protected:
    bool isUtf8CharacterBegin(char ch);
    vector<int> getUtf8CharacterCount(const string& text);
};

#endif // PARSE_H
