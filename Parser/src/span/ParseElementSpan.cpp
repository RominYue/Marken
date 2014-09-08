#include "ParseElementSpan.h"

ParseElementSpan::ParseElementSpan() : ParseElement() {
    openActivate = false;
    closeActivate = false;
}

bool ParseElementSpan::isBlockElement() const {
    return false;
}

qint32 ParseElementSpan::tryParse(const QString& text, qint32 offset) {
    UNUSED(text);
    UNUSED(offset);
    return 0;
}
