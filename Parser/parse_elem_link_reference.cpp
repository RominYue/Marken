#include "parse_elem_link_reference.h"
using namespace std;

ParseElementLinkReference::ParseElementLinkReference() : ParseElementLink() {
}

ParseElementType ParseElementLinkReference::type() const {
    return ParseElementType::TYPE_LINK_REFERENCE;
}
