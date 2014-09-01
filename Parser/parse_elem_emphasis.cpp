#include "parse_elem_emphasis.h"
using namespace std;

ParseElementEmphasis::ParseElementEmphasis() : ParseElementSpan() {
}

ParseElementType ParseElementEmphasis::type() const {
    return ParseElementType::TYPE_EMPHASIS;
}
