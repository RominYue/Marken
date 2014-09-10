#include "ParseElementHeaderAtx.h"

ParseElementHeaderAtx::ParseElementHeaderAtx() : ParseElementHeader() {
}

ParseElementType ParseElementHeaderAtx::type() const {
    return ParseElementType::TYPE_HEADER_ATX;
}

bool ParseElementHeaderAtx::tryParse(const QString &line, int offset, int& length) {
    int hashNum = 0;
    int lineLen = line.length();
    for (int i = offset; i < lineLen; ++i) {
        if (line[i] == '#') {
            ++hashNum;
        } else {
            if (!line[i].isSpace()) {
                return false;
            }
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

QString ParseElementHeaderAtx::generateOpenHtml() const {
    return this->generateOpenTag();
}

QString ParseElementHeaderAtx::generateCloseHtml() const {
    return this->generateCloseTag();
}
