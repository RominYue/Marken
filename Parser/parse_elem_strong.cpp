#include "parse_elem_strong.h"
using namespace std;

ParseElementStrong::ParseElementStrong() : ParseElementSpan() {
}

ParseElementType ParseElementStrong::type() const {
    return ParseElementType::TYPE_STRONG;
}

int ParseElementStrong::tryParse(const string& text, int offset) {
    char beginChar = text[offset];
    if (beginChar == '*' || beginChar == '_') {
        int length = text.length();
        if (offset + 1 < length) {
            if (text[offset + 1] == beginChar) {
                bool escape = false;
                bool hasText = false;
                for (int i = offset + 1; i < length; ++i) {
                    if (escape) {
                        escape = false;
                    } else {
                        if (text[i] == '\\') {
                            escape = true;
                        } else if (text[i] == beginChar) {
                            if (i + 1 < length) {
                                if (text[i + 1] == beginChar) {
                                    if (hasText) {
                                        return i + 2 - offset;
                                    }
                                    return 0;
                                }
                            }
                        } else if (text[i] != ' ' && text[i] != '\t') {
                            hasText = true;
                        }
                    }
                }
            }
        }
    }
    return 0;
}

string ParseElementStrong::generateOpenHtml() const {
    return "<strong>";
}

string ParseElementStrong::generateCloseHtml() const {
    return "</strong>";
}

string ParseElementStrong::innerText() const {
    return this->text.substr(2, this->text.length() - 4);
}

int ParseElementStrong::innerOffset() const {
    return 2;
}
