#include "parse_elems.h"
#include "parse_line_data.h"
using namespace std;

ParseLineData::ParseLineData() :
    _prev(nullptr), _next(nullptr),
    _future(),
    _elems(), _olds() {
}

ParseLineData::~ParseLineData() {
}

ParseLineData* ParseLineData::prev() const {
    return _prev;
}

ParseLineData* ParseLineData::next() const {
    return _next;
}

void ParseLineData::setNeighbor(ParseLineData *prevLine, ParseLineData *nextLine) {
    _prev = prevLine;
    _next = nextLine;
    if (_prev != nullptr) {
        _prev->_next = this;
    }
    if (_next != nullptr) {
        _next->_prev = this;
    }
}

void ParseLineData::removeFromList() {
    if (_prev != nullptr) {
        _prev->_next = _next;
    }
    if (_next != nullptr) {
        _next->_prev = _prev;
    }
    _prev = nullptr;
    _next = nullptr;
}

set<shared_ptr<ParseElem>>* ParseLineData::future() {
    return &_future;
}

void ParseLineData::insertToFuture(shared_ptr<ParseElem> elem) {
    _future.insert(elem);
}

vector<shared_ptr<ParseElem>>& ParseLineData::elems() {
    return _elems;
}

shared_ptr<ParseElem> ParseLineData::operator [](const int index) const {
    if (0 <= index && index < (int)_elems.size()) {
        return _elems[index];
    }
    return shared_ptr<ParseElem>(nullptr);
}

string ParseLineData::generateHtml() const {
    string html;
    for (auto elem : _elems) {
        if (elem->isBlockElement()) {
            html += static_pointer_cast<ParseElemBlock>(elem)->generateOpenHtml();
        } else {
            html += static_pointer_cast<ParseElemSpan>(elem)->generateHtml();
        }
    }
    for (auto it = _elems.rbegin(); it != _elems.rend(); ++it) {
        if ((*it)->isBlockElement()) {
            html += static_pointer_cast<ParseElemBlock>(*it)->generateCloseHtml();
        }
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
