#include "parse_elem_block.h"
using namespace std;

ParseElementBlock::ParseElementBlock() : ParseElement() {
    this->isVirtual = false;
}

bool ParseElementBlock::isBlockElement() const {
    return true;
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
