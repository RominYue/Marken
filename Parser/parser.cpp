#include "parser.h"
using namespace std;

Parser::Parser() {
    //ctor
}

Parser::~Parser() {
    //dtor
}

vector<string> Parser::parseToList(vector<string>& document) {
    return document;
}

string Parser::parseToHtml(vector<string>& document) {
    string html;
    vector<string> result = parseToList(document);
    for (auto line : result) {
        html += line + "\n";
    }
    return html;
}
