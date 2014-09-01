#include "parse_elem_strong.h"
using namespace std;

ParseElementStrong::ParseElementStrong() : ParseElementSpan() {
}

ParseElementType ParseElementStrong::type() const {
    return ParseElementType::TYPE_STRONG;
}
