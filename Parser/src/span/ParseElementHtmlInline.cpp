#include "ParseElementHtmlInline.h"

ParseElementHtmlInline::ParseElementHtmlInline() : ParseElementSpan() {
}

ParseElementType ParseElementHtmlInline::type() const {
    return ParseElementType::TYPE_HTML_INLINE;
}

qint32 ParseElementHtmlInline::tryParse(const QString& text, qint32 offset) {
    qint32 index = offset;
    if (this->findOpenTagOffset(text, index)) {
        if (this->matchToGt(text, index)) {
            return index - offset;
        }
    }
    index = offset;
    if (this->findCloseTagOffset(text, index)) {
        if (this->matchToGt(text, index)) {
            return index - offset;
        }
    }
    return 0;
}

QString ParseElementHtmlInline::generateOpenHtml() const {
    return this->text;
}
