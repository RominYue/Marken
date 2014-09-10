#include "ParseElementSpan.h"

ParseElementSpan::ParseElementSpan() : ParseElement() {
    openActivate = false;
    closeActivate = false;
}

bool ParseElementSpan::isBlockElement() const {
    return false;
}

int ParseElementSpan::tryParse(const QString& text, int offset) {
    UNUSED(text);
    UNUSED(offset);
    return 0;
}
