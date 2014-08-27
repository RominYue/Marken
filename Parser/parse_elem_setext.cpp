#include "parse_elem_setext.h"

ParseElemSetext::ParseElemSetext() :
    ParseElemHeader() {
}

ParseElemType ParseElemSetext::type() const {
    return ParseElemType::ELEM_HEADER_SETEXT;
}
