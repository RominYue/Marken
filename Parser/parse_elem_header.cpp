#include "parse_elem_header.h"
using namespace std;

ParseElemHeader::ParseElemHeader() :
    ParseElemBlock(),
    _level(1) {
}

int ParseElemHeader::level() const {
    return _level;
}

void ParseElemHeader::setLevel(const int val) {
    _level = val;
}

string ParseElemHeader::generateOpenHtml() const {
    string html = string("<h") + (char)('0' + _level) + string(">");
    return html;
}

string ParseElemHeader::generateCloseHtml() const {
    string html = string("</h") + (char)('0' + _level) + string(">");
    return html;
}

/**
 * Remove hashes and spaces in two end.
 */
string ParseElemHeader::getCleanHeader() const {
    int len = (int)_text.length();
    int left = _level;
    for (; left < len; ++left) {
        if (!isRemovableCharacter(_text[left])) {
            break;
        }
    }
    int right = len - 1;
    for (; right >= 0; --right) {
        if (!isRemovableCharacter(_text[right])) {
            ++right;
            break;
        }
    }
    if (right > 0 && right < len) {
        if (_text[right - 1] == '\\') {
            ++right;
        }
    }
    if (left < right) {
        return _text.substr(left, right - left);
    }
    return "";
}

bool ParseElemHeader::isRemovableCharacter(const char ch) const {
    return ch == ' ' || ch == '\t' || ch == '#';
}
