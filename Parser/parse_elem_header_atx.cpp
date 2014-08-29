#include "parse_elem_header_atx.h"
using namespace std;

ParseElementHeaderAtx::ParseElementHeaderAtx() : ParseElementHeader() {
}

ParseElementType ParseElementHeaderAtx::type() const {
    return ParseElementType::TYPE_HEADER_ATX;
}

bool ParseElementHeaderAtx::tryParse(const string &line, int offset, int& length) {
    int hashNum = 0;
    int lineLen = line.length();
    for (int i = offset; i < lineLen; ++i) {
        if (line[i] == '#') {
            ++hashNum;
        } else {
            break;
        }
    }
    if (1 <= hashNum && hashNum <= 6) {
        this->level = hashNum;
        length = lineLen - offset;
        return true;
    }
    return false;
}

string ParseElementHeaderAtx::generateOpenHtml() const {
    return this->generateOpenTag() + this->getCleanedHeader();
}

string ParseElementHeaderAtx::generateCloseHtml() const {
    return this->generateCloseTag();
}
