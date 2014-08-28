#include "parse_elem.h"
#include "parse_elem_html_block.h"
#include "parse_elem_factory.h"
using namespace std;

shared_ptr<ParseElement> ParseElementFactory::copy(const shared_ptr<ParseElement> element) const {
    ParseElement* newElement = nullptr;
    switch (element->type()) {
    case ParseElementType::TYPE_HTML_BLOCK:
        newElement = new ParseElementHtmlBlock();
        break;
    default:
        break;
    }
    if (newElement != nullptr) {
        *newElement = *element;
    }
    return shared_ptr<ParseElement>(newElement);
}
