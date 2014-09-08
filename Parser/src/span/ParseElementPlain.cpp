#include "ParseElementPlain.h"

ParseElementPlain::ParseElementPlain() : ParseElementSpan() {
}

ParseElementType ParseElementPlain::type() const {
    return ParseElementType::TYPE_PLAIN;
}

QString ParseElementPlain::generateOpenHtml() const {
    return this->htmlEscaped(text);
}
