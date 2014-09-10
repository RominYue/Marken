#include "ParseElementHeader.h"

ParseElementHeader::ParseElementHeader() : ParseElementBlock() {
}

int ParseElementHeader::getCleanStartIndex() const {
    int len = this->text.size();
    int start = len;
    for (int i = 0; i < len; ++i) {
        if (!text[i].isSpace() && text[i] != '#') {
            start = i;
            break;
        }
    }
    return start;
}

int ParseElementHeader::getCleanEndIndex() const {
    int end = 0;
    int len = this->text.size();
    for (int i = len - 1; i >= 0; --i) {
        if (!text[i].isSpace() && text[i] != '#') {
            if (text[i] == '\\') {
                if (i > 0 && text[i - 1] == '\\') {
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
    return end;
}

QString ParseElementHeader::getCleanedHeader() const {
    int start = this->getCleanStartIndex();
    int end = this->getCleanEndIndex();
    if (start < end) {
        return text.mid(start, end - start);
    }
    return "";
}

QString ParseElementHeader::generateOpenTag() const {
    return QString("<h") + (QChar)('0' + level) + QString(">");
}

QString ParseElementHeader::generateCloseTag() const {
    return QString("</h") + (QChar)('0' + level) + QString(">");
}
