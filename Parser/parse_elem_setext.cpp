#include "parse_elem_setext.h"

ParseElemSetext::ParseElemSetext() :
    ParseElemHeader() {
    setType(ParseElemType::ELEM_HEADER_SETEXT);
}

