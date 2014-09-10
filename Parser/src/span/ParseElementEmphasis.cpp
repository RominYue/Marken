#include "ParseElementEmphasis.h"

ParseElementEmphasis::ParseElementEmphasis() : ParseElementSpan() {
}

ParseElementType ParseElementEmphasis::type() const {
    return ParseElementType::TYPE_EMPHASIS;
}

int ParseElementEmphasis::tryParse(const QString& text, int offset) {
    QChar beginChar = text[offset];
    if (beginChar == '*' || beginChar == '_') {
        int length = text.length();
        bool escape = false;
        bool hasText = false;
        for (int i = offset + 1; i < length; ++i) {
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

int ParseElementEmphasis::innerOffset() const {
    return 1;
}
