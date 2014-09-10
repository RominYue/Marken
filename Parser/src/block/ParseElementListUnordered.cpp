#include "ParseLineData.h"
#include "ParseElementListUnordered.h"

ParseElementListUnordered::ParseElementListUnordered() : ParseElementList() {
}

ParseElementType ParseElementListUnordered::type() const {
    return ParseElementType::TYPE_LIST_UNORDERED;
}

bool ParseElementListUnordered::tryParse(const QString &line, int offset, int& length) {
    int lineLen = line.length();
    if (lineLen > offset) {
        if (line[offset].isSpace()) {
            if (parent->prev() == nullptr) {
                return false;
            }
            if (parent->prev()->getTypeAt(offset) == ParseElementType::TYPE_LIST_UNORDERED) {
                this->isVirtual = true;
                length = 1;
                return true;
            }
        } else if (line[offset] == '*' || line[offset] == '+' || line[offset] == '-') {
            if (offset + 1 == lineLen || line[offset + 1] == ' ' || line[offset + 1] == '\t') {
                this->isVirtual = false;
                length = 1;
                return true;
            }
        }
    }
    return false;
}

QString ParseElementListUnordered::getListOpenTag() const {
    return "<ul>";
}

QString ParseElementListUnordered::getListCloseTag() const {
    return "</ul>";
}
