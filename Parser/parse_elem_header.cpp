#include "parse_elem_header.h"
using namespace std;

ParseElementHeader::ParseElementHeader() : ParseElementBlock() {
}

int ParseElementHeader::getCleanStartIndex() const {
    int start = 0;
    int len = this->text.size();
    for (int i = 0; i < len; ++i) {
        if (text[i] != ' ' && text[i] != '\t' && text[i] != '#') {
            start = i;
            break;
        }
    }
    return start;
}

int ParseElementHeader::getCleanEndIndex() const {
    int end = this->text.size();
    int len = this->text.size();
    for (int i = len - 1; i >= 0; --i) {
        if (text[i] != ' ' && text[i] != '\t' && text[i] != '#') {
            if (i > 0 && text[i - 1] == '\\') {
                if (i > 1 && text[i - 2] != '\\') {
                    end = i + 1;
                }
                else {
                    end = i + 2;
                }
            }
            else {
                end = i + 1;
            }
            break;
        }
    }
    return end;
}

string ParseElementHeader::getCleanedHeader() const {
    int start = this->getCleanStartIndex();
    int end = this->getCleanEndIndex();
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
