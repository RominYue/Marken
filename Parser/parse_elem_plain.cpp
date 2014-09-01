#include "parse_elem_plain.h"
using namespace std;

ParseElementPlain::ParseElementPlain() : ParseElementSpan() {
}

ParseElementType ParseElementPlain::type() const {
    return ParseElementType::TYPE_PLAIN;
}

string ParseElementPlain::generateOpenHtml() const {
    int len = text.length();
    string html;
    for (int i = 0; i < len; ++i) {
        char ch = text[i];
        switch (ch) {
        case '<':
            html += "&lt;";
            break;
        case '>':
            html += "&gt;";
            break;
        case '&':
            html += "&amp;";
            break;
        default:
            html += ch;
            break;
        }
    }
    return html;
}
