#include "parse_elem_span.h"
using namespace std;

ParseElementSpan::ParseElementSpan() : ParseElement() {
    this->activate = true;
}

bool ParseElementSpan::isBlockElement() const {
    return false;
}

string ParseElementSpan::generateHtml() const {
    return "";
}

