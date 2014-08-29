#include "parse_elem.h"
#include "parse_elem_html_block.h"
#include "parse_elem_code_block.h"
#include "parse_elem_header_atx.h"
#include "parse_elem_header_setext.h"
#include "parse_elem_horizontal.h"
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
    case ParseElementType::TYPE_HEADER_ATX:
        newElement = new ParseElementHeaderAtx(*dynamic_pointer_cast<ParseElementHeaderAtx>(element));
        break;
    case ParseElementType::TYPE_HEADER_SETEXT:
        newElement = new ParseElementHeaderSetext(*dynamic_pointer_cast<ParseElementHeaderSetext>(element));
        break;
    case ParseElementType::TYPE_HORIZON:
        newElement = new ParseElementHorizontal(*dynamic_pointer_cast<ParseElementHorizontal>(element));
        break;
    default:
        break;
    }
    return shared_ptr<ParseElement>(newElement);
}
