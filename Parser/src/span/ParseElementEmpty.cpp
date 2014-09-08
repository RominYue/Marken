#include "ParseElementEmpty.h"

ParseElementEmpty::ParseElementEmpty() : ParseElementBlock() {
}

ParseElementType ParseElementEmpty::type() const {
    return ParseElementType::TYPE_EMPTY;
}
