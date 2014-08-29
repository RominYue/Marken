#include "parse_elem.h"
#include "parse_elem_html_block.h"
#include "parse_elem_code_block.h"
#include "parse_elem_factory.h"
using namespace std;

shared_ptr<ParseElement> ParseElementFactory::copy(const shared_ptr<ParseElement> element) const {
    ParseElement* newElement = nullptr;
    switch (element->type()) {
    case ParseElementType::TYPE_HTML_BLOCK:
		newElement = new ParseElementHtmlBlock(*dynamic_pointer_cast<ParseElementHtmlBlock>(element));
        break;
    case ParseElementType::TYPE_CODE_BLOCK:
		newElement = new ParseElementCodeBlock(*dynamic_pointer_cast<ParseElementCodeBlock>(element));
        break;
    default:
        break;
    }
    return shared_ptr<ParseElement>(newElement);
}
