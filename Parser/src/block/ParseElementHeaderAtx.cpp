#include "ParseElementHeaderAtx.h"

ParseElementHeaderAtx::ParseElementHeaderAtx() : ParseElementHeader() {
}

ParseElementType ParseElementHeaderAtx::type() const {
    return ParseElementType::TYPE_HEADER_ATX;
}

bool ParseElementHeaderAtx::tryParse(const QString &line, qint32 offset, qint32& length) {
    qint32 hashNum = 0;
    qint32 lineLen = line.length();
    for (qint32 i = offset; i < lineLen; ++i) {
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
