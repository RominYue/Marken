#include "parse_elem_link_inline.h"
using namespace std;

ParseElementLinkInline::ParseElementLinkInline() : ParseElementLink() {
}

ParseElementType ParseElementLinkInline::type() const {
    return ParseElementType::TYPE_LINK_INLINE;
}
