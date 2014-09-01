#include "parse_elem_link_label.h"
using namespace std;

ParseElementLinkLabel::ParseElementLinkLabel() : ParseElementLink() {
}

ParseElementType ParseElementLinkLabel::type() const {
    return ParseElementType::TYPE_LINK_LABEL;
}
