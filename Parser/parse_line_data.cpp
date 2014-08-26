#include "parse_line_data.h"
using namespace std;

ParseLineData::ParseLineData() :
    _elems(), _olds() {
}

ParseLineData::~ParseLineData() {
}

vector<shared_ptr<ParseElem>>& ParseLineData::elems() {
    return _elems;
}

shared_ptr<ParseElem> ParseLineData::operator [](const int index) const {
    if (0 <= index && index < (int)_elems.size()) {
        return _elems[index];
    }
    return nullptr;
}

string ParseLineData::generateHtml() const {
    string html;
    for (auto elem : _elems) {
        html += elem->generateHtml();
    }
    return html;
}

bool ParseLineData::isChanged() const {
    if (_olds.size() != _elems.size()) {
        return true;
    }
    int len = _olds.size();
    for (int i = 0; i < len; ++i) {
        if (_olds[i]->isEqual(_elems[i])) {
            return true;
        }
    }
    return false;
}

void ParseLineData::saveStruct() {
    _olds = _elems;
}
