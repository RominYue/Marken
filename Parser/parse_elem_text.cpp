#include "parse_elem_text.h"
using namespace std;

ParseElemText::ParseElemText() :
    ParseElemSpan() {
}

ParseElemType ParseElemText::type() const {
    return ParseElemType::ELEM_TEXT;
}

string ParseElemText::generateHtml() const {
    string html;
    int len = _text.length();
    for (int i = 0; i < len; ++i) {
        if (_text[i] == '<') {
            html += "&lt;";
        } else if (_text[i] == '>') {
            html += "&gt;";
        } else if (_text[i] == '&') {
            AmpersandStatus status = STATUS_AMP;
            for (int j = 1; i + j < len; ++j) {
                char ch = _text[i + j];
                switch (status) {
                case STATUS_AMP:
                    if ((ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z')) {
                        status = STATUS_ALPHA;
                    } else if (ch == '#') {
                        status = STATUS_HASH;
                    } else {
                        status = STATUS_FAILED;
                    }
                    break;
                case STATUS_ALPHA:
                    if ((ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z')) {
                        status = STATUS_ALPHA;
                    } else if (ch == ';') {
                        status = STATUS_ACCEPT;
                    } else {
                        status = STATUS_FAILED;
                    }
                    break;
                case STATUS_HASH:
                    if (ch >= '0' && ch <= '9') {
                        status = STATUS_DIGIT;
                    } else {
                        status = STATUS_FAILED;
                    }
                    break;
                case STATUS_DIGIT:
                    if (ch >= '0' && ch <= '9') {
                        status = STATUS_DIGIT;
                    } else if (ch == ';') {
                        status = STATUS_ACCEPT;
                    } else {
                        status = STATUS_FAILED;
                    }
                    break;
                case STATUS_ACCEPT:
                case STATUS_FAILED:
                default:
                    break;
                }
                if (status == STATUS_FAILED) {
                    html += "&amp;";
                    break;
                }
                if (status == STATUS_ACCEPT) {
                    html += _text.substr(i, j - i + 1);
                    i = j;
                    break;
                }
            }
        }
    }
    return html;
}
