#include "parse_elem_code_inline.h"
using namespace std;

ParseElementCodeInline::ParseElementCodeInline() : ParseElementSpan() {
}

ParseElementType ParseElementCodeInline::type() const {
    return ParseElementType::TYPE_CODE_INLINE;
}
