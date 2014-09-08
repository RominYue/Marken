#include "ParseElementHeader.h"

ParseElementHeader::ParseElementHeader() : ParseElementBlock() {
}

qint32 ParseElementHeader::getCleanStartIndex() const {
    qint32 len = this->text.size();
    qint32 start = len;
    for (qint32 i = 0; i < len; ++i) {
        if (!text[i].isSpace() && text[i] != '#') {
            start = i;
            break;
        }
    }
    return start;
}

qint32 ParseElementHeader::getCleanEndIndex() const {
    qint32 end = 0;
    qint32 len = this->text.size();
    for (qint32 i = len - 1; i >= 0; --i) {
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
    qint32 start = this->getCleanStartIndex();
    qint32 end = this->getCleanEndIndex();
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
