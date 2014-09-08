#include "ParseElementEmphasis.h"

ParseElementEmphasis::ParseElementEmphasis() : ParseElementSpan() {
}

ParseElementType ParseElementEmphasis::type() const {
    return ParseElementType::TYPE_EMPHASIS;
}

qint32 ParseElementEmphasis::tryParse(const QString& text, qint32 offset) {
    QChar beginChar = text[offset];
    if (beginChar == '*' || beginChar == '_') {
        qint32 length = text.length();
        bool escape = false;
        bool hasText = false;
        for (qint32 i = offset + 1; i < length; ++i) {
            if (escape) {
                escape = false;
            } else {
                if (text[i] == '\\') {
                    escape = true;
                } else if (text[i] == beginChar) {
                    if (hasText) {
                        return i + 1 - offset;
                    }
                    return 0;
                } else if (!text[i].isSpace()) {
                    hasText = true;
                }
            }
        }
    }
    return 0;
}

QString ParseElementEmphasis::generateOpenHtml() const {
    return "<em>";
}

QString ParseElementEmphasis::generateCloseHtml() const {
    return "</em>";
}

QString ParseElementEmphasis::innerText() const {
    return this->text.mid(1, this->text.length() - 2);
}

qint32 ParseElementEmphasis::innerOffset() const {
    return 1;
}
