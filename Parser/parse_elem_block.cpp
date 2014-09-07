#include "parse_line.h"
#include "parse_elem_block.h"
using namespace std;

ParseElementBlock::ParseElementBlock() : ParseElement() {
    this->isVirtual = false;
}

bool ParseElementBlock::isBlockElement() const {
    return true;
}

bool ParseElementBlock::stopParsing(int offset) const {
    if (parent->prev() != nullptr) {
        if (parent->prev()->lastType() == ParseElementType::TYPE_PARAGRAPH) {
            auto last = parent->prev()->lastElement();
            if (offset >= last->offset + 4) {
                return true;
            }
        }
    }
    return false;
}

bool ParseElementBlock::tryParse(const string &line, int offset, int& length) {
    UNUSED(line);
    UNUSED(offset);
    UNUSED(length);
    return false;
}

bool ParseElementBlock::inheritable() const {
    return false;
}
