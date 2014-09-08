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
    string html;
    int len = text.length();
    int tab = 0;
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
        case '\t':
            if (tab == 0) {
                html += "    ";
            } else {
                for (int j = 0; j < 4 - tab; ++j) {
                    html += " ";
                }
            }
            tab = 0;
            break;
        default:
            html += ch;
            break;
        }
        if (ch != '\t') {
            if (((ch & 0x80) == 0) || ((ch & 0xC0) == 0xC0)) {
                tab += 1;
                if (tab == 4) {
                    tab = 0;
                }
            }
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
