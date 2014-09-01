#include "parse_elem_amp.h"
using namespace std;

ParseElementAmp::ParseElementAmp() : ParseElementSpan() {
}

ParseElementType ParseElementAmp::type() const {
    return ParseElementType::TYPE_AMP;
}

int ParseElementAmp::tryParse(const string& text, int offset) {
    if (text[offset] == '&') {
        Status status = STATUS_AMP;
        int length = text.length();
        for (int i = offset + 1; i < length; ++i) {
            switch (status) {
            case STATUS_AMP:
                if (text[i] == '#') {
                    status = STATUS_HASH;
                } else if (isalpha(text[i])) {
                    status = STATUS_ALPHA;
                } else {
                    return 0;
                }
                break;
            case STATUS_ALPHA:
                if (isalpha(text[i])) {
                    status = STATUS_ALPHA;
                } else if (text[i] == ';') {
                    status = STATUS_DELIMITER;
                } else {
                    return 0;
                }
                break;
            case STATUS_HASH:
                if (isdigit(text[i])) {
                    status = STATUS_DIGIT;
                } else {
                    return 0;
                }
                break;
            case STATUS_DIGIT:
                if (isdigit(text[i])) {
                    status = STATUS_DIGIT;
                } else if (text[i] == ';') {
                    status = STATUS_DELIMITER;
                } else {
                    return 0;
                }
                break;
            case STATUS_DELIMITER:
            default:
                break;
            }
            if (status == STATUS_DELIMITER) {
                return i + 1 - offset;
            }
        }
    }
    return 0;
}

string ParseElementAmp::generateOpenHtml() const {
    return this->text;
}
