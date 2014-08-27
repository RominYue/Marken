#include "parse_elem.h"
using namespace std;

ParseElem::ParseElem() :
    _indent(0),
    _length(),
    _text(),
    _parent(nullptr) {
}

ParseElem::~ParseElem() {
}

int ParseElem::indent() const {
    return _indent;
}

void ParseElem::setIndent(const int val) {
    _indent = val;
}

int ParseElem::length() const {
    return _length;
}

void ParseElem::setLength(const int val) {
    _length = val;
}

const std::string& ParseElem::text() const {
    return _text;
}

void ParseElem::setText(const std::string& val) {
    _text = val;
}

ParseLineData* ParseElem::parent() const {
    return _parent;
}

void ParseElem::setParent(ParseLineData* val) {
    _parent = val;
}

ParseElemType ParseElem::type() const {
    return ParseElemType::ELEM_INVALID;
}

bool ParseElem::isEqual(const shared_ptr<ParseElem> elem) const {
    return type() == elem->type() && indent() == elem->indent();
}

bool ParseElem::tryParse(std::string text, int offset, int &len) {

    return false;
}
