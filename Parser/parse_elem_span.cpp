#include "parse_elem_span.h"
using namespace std;

ParseElemSpan::ParseElemSpan() :
    ParseElem() {
}

bool ParseElemSpan::isBlockElement() const {
    return true;
}

string ParseElemSpan::generateHtml() const {
    return "";
}
