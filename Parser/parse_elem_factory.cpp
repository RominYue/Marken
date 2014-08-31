#include "parse_elem.h"
#include "parse_elem_block.h"
#include "parse_elem_html_block.h"
#include "parse_elem_code_block.h"
#include "parse_elem_header_atx.h"
#include "parse_elem_header_setext.h"
#include "parse_elem_horizontal.h"
#include "parse_elem_list_unordered.h"
#include "parse_elem_list_ordered.h"
#include "parse_elem_quote.h"
#include "parse_elem_paragraph.h"
#include "parse_elem_factory.h"
#include "parse_elem_span.h"
#include "parse_elem_escape.h"
#include "parse_elem_amp.h"
#include "parse_elem_code_inline.h"
#include "parse_elem_emphasis.h"
#include "parse_elem_strong.h"
#include "parse_elem_html_inline.h"
#include "parse_elem_link_inline.h"
#include "parse_elem_link_label.h"
#include "parse_elem_link_reference.h"
#include "parse_elem_image.h"
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
    case ParseElementType::TYPE_LIST_UNORDERED:
        newElement = new ParseElementListUnordered(*dynamic_pointer_cast<ParseElementListUnordered>(element));
        break;
    case ParseElementType::TYPE_LIST_ORDERED:
        newElement = new ParseElementListOrdered(*dynamic_pointer_cast<ParseElementListOrdered>(element));
        break;
    case ParseElementType::TYPE_QUOTE:
        newElement = new ParseElementQuote(*dynamic_pointer_cast<ParseElementQuote>(element));
        break;
    case ParseElementType::TYPE_PARAGRAPH:
        newElement = new ParseElementParagraph(*dynamic_pointer_cast<ParseElementParagraph>(element));
        break;
    case ParseElementType::TYPE_ESCAPE:
        newElement = new ParseElementEscape(*dynamic_pointer_cast<ParseElementEscape>(element));
        break;
    case ParseElementType::TYPE_CODE_INLINE:
        newElement = new ParseElementCodeInline(*dynamic_pointer_cast<ParseElementCodeInline>(element));
        break;
    case ParseElementType::TYPE_EMPHASIS:
        newElement = new ParseElementEmphasis(*dynamic_pointer_cast<ParseElementEmphasis>(element));
        break;
    case ParseElementType::TYPE_STRONG:
        newElement = new ParseElementStrong(*dynamic_pointer_cast<ParseElementStrong>(element));
        break;
    case ParseElementType::TYPE_HTML_INLINE:
        newElement = new ParseElementHtmlInline(*dynamic_pointer_cast<ParseElementHtmlInline>(element));
        break;
    case ParseElementType::TYPE_LINK_INLINE:
        newElement = new ParseElementLinkInline(*dynamic_pointer_cast<ParseElementLinkInline>(element));
        break;
    case ParseElementType::TYPE_LINK_LABEL:
        newElement = new ParseElementLinkLabel(*dynamic_pointer_cast<ParseElementLinkLabel>(element));
        break;
    case ParseElementType::TYPE_LINK_REFERENCE:
        newElement = new ParseElementLinkReference(*dynamic_pointer_cast<ParseElementLinkReference>(element));
        break;
    case ParseElementType::TYPE_IMAGE:
        newElement = new ParseElementImage(*dynamic_pointer_cast<ParseElementImage>(element));
        break;
    default:
        break;
    }
    return shared_ptr<ParseElement>(newElement);
}

shared_ptr<ParseElementBlock> ParseElementFactory::copy(const shared_ptr<ParseElementBlock> element) const {
    return dynamic_pointer_cast<ParseElementBlock>(copy(dynamic_pointer_cast<ParseElement>(element)));
}

shared_ptr<ParseElementSpan> ParseElementFactory::copy(const shared_ptr<ParseElementSpan> element) const {
    return dynamic_pointer_cast<ParseElementSpan>(copy(dynamic_pointer_cast<ParseElement>(element)));
}
