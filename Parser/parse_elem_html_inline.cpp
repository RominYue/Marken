#include "parse_elem_html_inline.h"
using namespace std;

ParseElementHtmlInline::ParseElementHtmlInline() : ParseElementSpan() {
}

ParseElementType ParseElementHtmlInline::type() const {
    return ParseElementType::TYPE_HTML_INLINE;
}

int ParseElementHtmlInline::tryParse(const string& text, int offset) {
    int index = offset;
    if (this->findOpenTagOffset(text, index)) {
        if (this->matchToGt(text, index)) {
            return index - offset;
        }
    }
    index = offset;
    if (this->findCloseTagOffset(text, index)) {
        if (this->matchToGt(text, index)) {
            return index - offset;
        }
    }
    return 0;
}

string ParseElementHtmlInline::generateOpenHtml() const {
    return this->text;
}
