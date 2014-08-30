#include "parse_elem_span.h"
using namespace std;

ParseElementSpan::ParseElementSpan() : ParseElement() {
}

bool ParseElementSpan::isBlockElement() const {
    return false;
}

string ParseElementSpan::generateHtml() const {
    return "";
}

