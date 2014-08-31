#include <memory>
#include "parse_dynamic.h"
#include "parse_static.h"
#include "parse_line.h"
using namespace std;

StaticParser::StaticParser() : Parser() {
}

vector<string> StaticParser::parseToHtmlList(const vector<string>& document) const {
    vector<string> htmlList;
    vector<shared_ptr<ParseLine>> dataList;
    DynamicParser parser;
    for (auto line : document) {
        shared_ptr<ParseLine> data(new ParseLine());
        if (dataList.size() == 0) {
            parser.parseLine(data.get(), line);
        } else {
            data->setNeighbor((*dataList.rbegin()).get(), nullptr);
            parser.parseLine(data.get(), line);
        }
        dataList.push_back(data);
    }
    for (auto data : dataList) {
        htmlList.push_back(data->generateHtml());
    }
    return htmlList;
}

string StaticParser::parseToHtml(const vector<string>& document) const {
    string html;
    vector<string> htmlList = this->parseToHtmlList(document);
    for (auto line : htmlList) {
        html += line + "\n";
    }
    return html;
}
