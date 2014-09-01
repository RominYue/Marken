#include "parse_line.h"
#include "parse_elem.h"
using namespace std;

ParseElement::ParseElement() {
    offset = 0;
    utf8Offset = 0;
    utf8Length = 0;
    parent = nullptr;
}

ParseElementType ParseElement::type() const {
    return ParseElementType::TYPE_INVALID;
}

bool ParseElement::isBlockElement() const {
    return false;
}

bool ParseElement::operator ==(shared_ptr<ParseElement> element) const {
    return this->type() == element->type() && this->offset == element->offset;
}

string ParseElement::innerText() const {
    return "";
}

int ParseElement::innerOffset() const {
    return 0;
}

string ParseElement::translateAmp(const string& text) const {
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

string ParseElement::generateOpenHtml() const {
    return "";
}

string ParseElement::generateCloseHtml() const {
    return "";
}


