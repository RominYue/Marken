#include "parse_elem_span.h"
using namespace std;

ParseElementSpan::ParseElementSpan() : ParseElement() {
}

bool ParseElementSpan::isBlockElement() const {
    return false;
}

int ParseElementSpan::tryParse(const string& text, int offset, int length) {
    UNUSED(text);
    UNUSED(offset);
    UNUSED(length);
    return 0;
}

string ParseElementSpan::generateHtml() const {
    return "";
}

