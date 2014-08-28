#include "parse_line.h"
#include "parse_elem.h"
using namespace std;

#define UNUSED(x) (void)(x)

ParseElement::ParseElement() {
    offset = 0;
    utf8Offset = 0;
    utf8Length = 0;
    parent = nullptr;
}

ParseElementType ParseElement::type() const {
    return ParseElementType::TYPE_INVALID;
}

bool ParseElement::isBlockElement() const {
    return false;
}

bool ParseElement::operator ==(shared_ptr<ParseElement> element) const {
    return this->type() == element->type() && this->offset == element->offset;
}




