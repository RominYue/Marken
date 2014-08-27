#include "parse_elem_atx.h"
using namespace std;

ParseElemAtx::ParseElemAtx() :
    ParseElemHeader() {
}

ParseElemType ParseElemAtx::type() const {
    return ParseElemType::ELEM_HEADER_ATX;
}
