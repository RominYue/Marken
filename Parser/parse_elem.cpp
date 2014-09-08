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

string ParseElement::innerText() const {
    return "";
}

int ParseElement::innerOffset() const {
    return 0;
}

void ParseElement::remove() {
}

string ParseElement::removeSideSpaces(const string& text) const {
    int length = text.length();
    for (int i = 0; i < length; ++i) {
        if (!isspace(text[i])) {
            for (int j = length - 1; j > i; --j) {
                if (!isspace(text[j])) {
                    return text.substr(i, j + 1 - i);
                }
            }
        }
    }
    return "";
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
        case '"':
            html += "&quot;";
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

bool ParseElement::isdigit(char ch) const {
    return '0' <= ch && ch <= '9';
}

bool ParseElement::isalpha(char ch) const {
    return ('a' <= ch && ch <= 'z') || ('A' <= ch && ch <= 'Z');
}

bool ParseElement::isspace(char ch) const {
    return ch == ' ' || ch == '\t';
}
