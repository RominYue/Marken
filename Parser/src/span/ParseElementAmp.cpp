#include "ParseElementAmp.h"

ParseElementAmp::ParseElementAmp() : ParseElementSpan() {
}

ParseElementType ParseElementAmp::type() const {
    return ParseElementType::TYPE_AMP;
}

qint32 ParseElementAmp::tryParse(const QString& text, qint32 offset) {
    if (text[offset] == '&') {
        Status status = STATUS_AMP;
        qint32 length = text.length();
        for (qint32 i = offset + 1; i < length; ++i) {
            switch (status) {
            case STATUS_AMP:
                if (text[i] == QChar('#')) {
                    status = STATUS_HASH;
                } else if (text[i].isLetter()) {
                    status = STATUS_ALPHA;
                } else {
                    return 0;
                }
                break;
            case STATUS_ALPHA:
                if (text[i].isLetter()) {
                    status = STATUS_ALPHA;
                } else if (text[i] == QChar(';')) {
                    status = STATUS_DELIMITER;
                } else {
                    return 0;
                }
                break;
            case STATUS_HASH:
                if (text[i].isDigit()) {
                    status = STATUS_DIGIT;
                } else {
                    return 0;
                }
                break;
            case STATUS_DIGIT:
                if (text[i].isDigit()) {
                    status = STATUS_DIGIT;
                } else if (text[i] == QChar(';')) {
                    status = STATUS_DELIMITER;
                } else {
                    return 0;
                }
                break;
            case STATUS_DELIMITER:
            default:
                break;
            }
            if (status == STATUS_DELIMITER) {
                return i + 1 - offset;
            }
        }
    }
    return 0;
}

QString ParseElementAmp::generateOpenHtml() const {
    return this->text;
}
