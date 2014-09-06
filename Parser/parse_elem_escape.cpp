#include "parse_elem_escape.h"

ParseElementEscape::ParseElementEscape() : ParseElementSpan() {
}

ParseElementType ParseElementEscape::type() const {
    return ParseElementType::TYPE_ESCAPE;
}

int ParseElementEscape::tryParse(const string& text, int offset) {
    int length = text.length();
    if (text[offset] == '\\') {
        if (offset + 1 < length) {
            switch (text[offset + 1]) {
            case '\\':
            case '`':
            case '*':
            case '_':
            case '{': case '}':
            case '[': case ']':
            case '(': case ')':
            case '#':
            case '+':
            case '-':
            case '.':
            case '!':
            case '~':
                this->_escaped = text[offset + 1];
                return 2;
                break;
            default:
                return 0;
            }
        }
    }
    return 0;
}

string ParseElementEscape::generateOpenHtml() const {
    return string() + this->_escaped;
}
