#include "parse_elem_span.h"
using namespace std;

Parseblockspan::Parseblockspan() : ParseElement() {
    this->activate = true;
}

bool Parseblockspan::isBlockElement() const {
    return false;
}

string Parseblockspan::generateHtml() const {
    return "";
}

