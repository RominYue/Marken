#include "parse_elem_atx.h"
using namespace std;

ParseElemAtx::ParseElemAtx() :
    ParseElemHeader() {
    setType(ParseElemType::ELEM_HEADER_ATX);
}
