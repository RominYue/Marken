#include "parse_elem_header.h"
using namespace std;

ParseElementHeader::ParseElementHeader() : ParseElementBlock() {
}

string ParseElementHeader::getCleanedHeader() const {
    int start = 0;
    int end = this->text.size();
    int len = this->text.size();
    for (int i = 0; i < len; ++i) {
        if (text[i] != ' ' && text[i] != '\t' && text[i] != '#') {
            start = i;
            break;
        }
    }
    for (int i = len - 1; i >= 0; --i) {
        if (text[i] != ' ' && text[i] != '\t' && text[i] != '#') {
            if (i > 0 && text[i - 1] == '\\') {
                if (i > 1 && text[i - 2] != '\\') {
                    end = i + 1;
                } else {
                    end = i + 2;
                }
            } else {
                end = i + 1;
            }
            break;
        }
    }
    if (start < end) {
        return this->translateAmp(text.substr(start, end - start));
    }
    return "";
}

string ParseElementHeader::generateOpenTag() const {
    return string("<h") + (char)('0' + level) + string(">");
}

string ParseElementHeader::generateCloseTag() const {
    return string("</h") + (char)('0' + level) + string(">");
}
