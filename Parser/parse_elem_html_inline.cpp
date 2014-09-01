#include "parse_elem_html_inline.h"
using namespace std;

ParseElementHtmlInline::ParseElementHtmlInline() : ParseElementSpan() {
}

ParseElementType ParseElementHtmlInline::type() const {
    return ParseElementType::TYPE_HTML_INLINE;
}
