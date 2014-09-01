#include "parse_elem_plain.h"
using namespace std;

ParseElementPlain::ParseElementPlain() : ParseElementSpan() {
}

ParseElementType ParseElementPlain::type() const {
    return ParseElementType::TYPE_PLAIN;
}

string ParseElementPlain::generateOpenHtml() const {
    return this->text;
}
