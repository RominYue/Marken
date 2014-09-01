#include "parse_elem_amp.h"
using namespace std;

ParseElementAmp::ParseElementAmp() : ParseElementSpan() {
}

ParseElementType ParseElementAmp::type() const {
    return ParseElementType::TYPE_AMP;
}
