#include "ParseLineData.h"
#include "ParseElementListOrdered.h"

ParseElementListOrdered::ParseElementListOrdered() : ParseElementList() {
}

ParseElementType ParseElementListOrdered::type() const {
    return ParseElementType::TYPE_LIST_ORDERED;
}

bool ParseElementListOrdered::tryParse(const QString &line, int offset, int& length) {
    int lineLen = line.length();
    if (lineLen > offset) {
        if (line[offset].isSpace()) {
            if (parent->prev() == nullptr) {
                return false;
            }
            if (parent->prev()->getTypeAt(offset) == ParseElementType::TYPE_LIST_ORDERED) {
                this->isVirtual = true;
                length = 1;
                return true;
            }
        } else if (line[offset].isDigit()) {
            int index = offset;
            for (++index; index < lineLen; ++index) {
                if (!line[index].isDigit()) {
                    break;
                }
            }
            if (index == lineLen) {
                return false;
            }
            if (line[index] == '.') {
                this->isVirtual = false;
                length = index + 1 - offset;
                return true;
            }
        }
    }
    return false;
}

QString ParseElementListOrdered::getListOpenTag() const {
    return "<ol>";
}

QString ParseElementListOrdered::getListCloseTag() const {
    return "</ol>";
}
