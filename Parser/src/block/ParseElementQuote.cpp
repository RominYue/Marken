#include "ParseLineData.h"
#include "ParseElementQuote.h"

ParseElementQuote::ParseElementQuote() : ParseElementBlock() {
}

ParseElementType ParseElementQuote::type() const {
    return ParseElementType::TYPE_QUOTE;
}

bool ParseElementQuote::tryParse(const QString &line, qint32 offset, qint32& length) {
    qint32 lineLen = line.length();
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
        } else if (line[offset] == '>') {
            if (offset + 1 == lineLen || line[offset + 1].isSpace()) {
                this->isVirtual = false;
                length = 1;
                return true;
            }
        }
    }
    return false;
}

bool ParseElementQuote::inheritable() const {
    return true;
}

QString ParseElementQuote::generateOpenHtml() const {
    if (parent->prev() == nullptr) {
        return "<blockquote>";
    }
    if (parent->prev()->getTypeAt(offset) != ParseElementType::TYPE_QUOTE) {
        return "<blockquote>";
    }
    return "";
}

QString ParseElementQuote::generateCloseHtml() const {
    if (parent->next() == nullptr) {
        return "</blockquote>";
    }
    if (parent->next()->getTypeAt(offset) != ParseElementType::TYPE_QUOTE) {
        return "</blockquote>";
    }
    return "";
}