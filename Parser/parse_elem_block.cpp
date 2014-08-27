#include "parse_elem_block.h"
using namespace std;

ParseElemBlock::ParseElemBlock() :
    ParseElem() {
}

bool ParseElemBlock::isBlockElement() const {
    return true;
}

string ParseElemBlock::generateOpenHtml() const {
    return "";
}

string ParseElemBlock::generateCloseHtml() const {
    return "";
}
