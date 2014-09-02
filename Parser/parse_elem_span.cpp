#include "parse_elem_span.h"
using namespace std;

ParseElementSpan::ParseElementSpan() : ParseElement() {
    openActivate = false;
    closeActivate = false;
}

bool ParseElementSpan::isBlockElement() const {
    return false;
}

int ParseElementSpan::tryParse(const string& text, int offset) {
    UNUSED(text);
    UNUSED(offset);
    return 0;
}
