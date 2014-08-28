#include "parse_elem_block.h"
using namespace std;

#define UNUSED(x) (void)x;

ParseElementBlock::ParseElementBlock() : ParseElement() {
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

string ParseElementBlock::generateOpenHtml() const {
    return "";
}

string ParseElementBlock::generateCloseHtml() const {
    return "";
}
