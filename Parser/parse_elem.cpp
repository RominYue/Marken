#include "parse_elem.h"
using namespace std;

ParseElem::ParseElem() :
    _indent(0),
    _type(ParseElemType::ELEM_INVALID),
    _text() {
}

ParseElem::~ParseElem() {
}

int ParseElem::indent() const {
    return _indent;
}

void ParseElem::setIndent(const int val) {
    _indent = val;
}

ParseElemType ParseElem::type() const {
    return _type;
}

void ParseElem::setType(const ParseElemType val) {
    _type = val;
}

const std::string& ParseElem::text() const {
    return _text;
}

void ParseElem::setText(const std::string& val) {
    _text = val;
}

bool ParseElem::isEqual(const shared_ptr<ParseElem> elem) const {
    return _type == elem->_type && _indent == elem->_indent;
}

string ParseElem::generateHtml() const {
    return "";
}
