#include <fstream>
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

vector<string> StaticParser::parseToHtmlList(const string& filePath) const {
    vector<string> document;
    this->readDocument(filePath, document);
    return this->parseToHtmlList(document);
}

string StaticParser::parseToHtml(const string& filePath) const {
    vector<string> document;
    this->readDocument(filePath, document);
    return this->parseToHtml(document);
}

void StaticParser::parseToFile(const string& srcPath, const string& tarPath) const {
    auto document = parseToHtmlList(srcPath);
    this->saveDocument(tarPath, document);
}

void StaticParser::readDocument(const string& filePath, vector<string>& document) const {
    fstream fin;
    fin.open(filePath, ios::in | ios::binary);
    string buffer;
    while (getline(fin, buffer)) {
        document.push_back(buffer);
    }
    fin.close();
}

void StaticParser::saveDocument(const string& filePath, vector<string>& document) const {
    fstream fout;
    fout.open(filePath, ios::out | ios::binary);
    for (auto line : document) {
        fout << line << endl;
    }
    fout.close();
}
