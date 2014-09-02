#include "parse.h"
using namespace std;

Parser::Parser() {
}

Parser::~Parser() {
}

bool Parser::isUtf8CharacterBegin(char ch) {
    return ((ch & 0x80) == 0) || ((ch & 0xC0) == 0xC0);
}

vector<int> Parser::getUtf8CharacterCount(const string& text) {
    vector<int> wordCount;
    wordCount.push_back(0);
    for (auto ch : text) {
        int last = 0;
        if (wordCount.size() > 0) {
            last = *wordCount.rbegin();
        }
        if (this->isUtf8CharacterBegin(ch)) {
            wordCount.push_back(last + 1);
        } else {
            wordCount.push_back(last);
        }
    }
    return wordCount;
}
