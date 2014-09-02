#include "parse_elem_empty.h"
using namespace std;

ParseElementEmpty::ParseElementEmpty() : ParseElementBlock() {
}

ParseElementType ParseElementEmpty::type() const {
    return ParseElementType::TYPE_EMPTY;
}
