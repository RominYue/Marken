#include "ParseElementCodeInline.h"

ParseElementCodeInline::ParseElementCodeInline() : ParseElementSpan() {
}

ParseElementType ParseElementCodeInline::type() const {
    return ParseElementType::TYPE_CODE_INLINE;
}

qint32 ParseElementCodeInline::tryParse(const QString& text, qint32 offset) {
    if (text[offset] == '`') {
        qint32 index = offset;
        qint32 length = text.length();
        this->_backtickNum = 1;
        for (++index; index < length; ++index) {
            if (text[index] == '`') {
                ++this->_backtickNum;
            } else {
                break;
            }
        }
        qint32 num = 0;
        bool escape = false;
        for (++index; index < length; ++index) {
            if (escape) {
                escape = false;
            } else {
                if (text[index] == '`') {
                    if (++num >= this->_backtickNum) {
                        return index + 1 - offset;
                    }
                } else {
                    num = 0;
                    if (text[index] == '\\') {
                        escape = true;
                    }
                }
            }
        }
    }
    return 0;
}

QString ParseElementCodeInline::generateOpenHtml() const  {
    auto code = this->text.mid(this->_backtickNum, this->text.length() - this->_backtickNum * 2);
    return "<code>" + this->htmlEscaped(code.trimmed());
}

QString ParseElementCodeInline::generateCloseHtml() const {
    return "</code>";
}
