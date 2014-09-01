#include "parse_elem_image.h"
using namespace std;

ParseElementImage::ParseElementImage() : ParseElementSpan() {
}

ParseElementType ParseElementImage::type() const {
    return ParseElementType::TYPE_IMAGE;
}
