#include "parser.h"
using namespace std;

Parser::Parser() :
    _blockElems(),
    _spanElems() {
}

Parser::~Parser() {
}

void Parser::parseLine(ParseLineData* data, string line) {
    int offset = 0, len = 0;
    int lineLen = (int)line.size();
    while (offset < lineLen) {
        if (data->future()->size() > 0) {
            auto it = data->future()->begin();
            if ((*it)->indent() == offset) {
                data->elems().push_back(*it);
                offset += (*it)->length();
                data->future()->erase(it);
                continue;
            }
        }
        bool hasBlockElem = false;
        bool isParagraph = false;
        for (auto elem : _blockElems) {
            elem->setParent(data);
            if (elem->tryParse(line, offset, len)) {
                data->elems().push_back(elem);
                offset += len;
                hasBlockElem = true;
                if (elem->type() == ParseElemType::ELEM_PARAGRAPH) {
                    isParagraph = true;
                }
                break;
            }
        }
        if (!hasBlockElem || isParagraph) {
            break;
        }
    }
    while (offset < lineLen) {
        if (data->future()->size() > 0) {
            auto it = data->future()->begin();
            if ((*it)->indent() == offset) {
                data->elems().push_back(*it);
                offset += (*it)->length();
                data->future()->erase(it);
                continue;
            }
        }
        for (auto elem : _spanElems) {
            elem->setParent(data);
            if (elem->tryParse(line, offset, len)) {
                data->elems().push_back(elem);
                offset += len;
                break;
            }
        }
    }
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
        shared_ptr<ParseLineData> data(new ParseLineData());
        parseLine(data.get(), document[0]);
        dataList.push_back(data);
    }
    int len = document.size();
    for (int i = 1; i < len; ++i) {
        shared_ptr<ParseLineData> data(new ParseLineData());
        data->setNeighbor((*dataList.rbegin()).get(), nullptr);
        parseLine(data.get(), document[i]);
        dataList.push_back(data);
    }
    return dataList;
}

bool Parser::isUtf8FirstCharacter(const char ch) const {
    return (ch & 0x80) == 0 || (ch & 0xC0) == 0xC0;
}
