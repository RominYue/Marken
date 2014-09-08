#include "ParseElementStrong.h"

ParseElementStrong::ParseElementStrong() : ParseElementSpan() {
}

ParseElementType ParseElementStrong::type() const {
    return ParseElementType::TYPE_STRONG;
}

qint32 ParseElementStrong::tryParse(const QString& text, qint32 offset) {
    QChar beginChar = text[offset];
    if (beginChar == '*' || beginChar == '_') {
        qint32 length = text.length();
        if (offset + 1 < length) {
            if (text[offset + 1] == beginChar) {
                bool escape = false;
                bool hasText = false;
                for (qint32 i = offset + 1; i < length; ++i) {
                    if (escape) {
                        escape = false;
                    } else {
                        if (text[i] == '\\') {
                            escape = true;
                        } else if (text[i] == beginChar) {
                            if (i + 1 < length) {
                                if (text[i + 1] == beginChar) {
                                    if (hasText) {
                                        return i + 2 - offset;
                                    }
                                    return 0;
                                }
                            }
                        } else if (!text[i].isSpace()) {
                            hasText = true;
                        }
                    }
                }
            }
        }
    }
    return 0;
}

QString ParseElementStrong::generateOpenHtml() const {
    return "<strong>";
}

QString ParseElementStrong::generateCloseHtml() const {
    return "</strong>";
}

QString ParseElementStrong::innerText() const {
    return this->text.mid(2, this->text.length() - 4);
}

qint32 ParseElementStrong::innerOffset() const {
    return 2;
}
