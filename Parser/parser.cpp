#include "parser.h"
using namespace std;

Parser::Parser() {
}

Parser::~Parser() {
}

shared_ptr<ParseLineData> Parser::parseLine(shared_ptr<ParseLineData> data, string line) {
    line += "1";
    return data;
}

vector<string> Parser::parseToList(vector<string>& document) {
    auto dataList = parseToDataList(document);
    vector<string> htmlList;
    for (auto data : dataList) {
        htmlList.push_back(data->generateHtml());
    }
    return htmlList;
}

string Parser::parseToHtml(vector<string>& document) {
    auto dataList = parseToDataList(document);
    string html;
    for (auto data : dataList) {
        html += data->generateHtml() + "\n";
    }
    return html;
}

vector<shared_ptr<ParseLineData>> Parser::parseToDataList(vector<string>& document) {
    vector<shared_ptr<ParseLineData>> dataList;
    if (document.size() > 0) {
        dataList.push_back(parseLine(nullptr, document[0]));
    }
    int len = document.size();
    for (int i = 1; i < len; ++i) {
        dataList.push_back(parseLine(*dataList.rbegin(), document[i]));
    }
    return dataList;
}
