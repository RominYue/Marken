#include "ParseElement.h"
#include "ParseElementBlock.h"
#include "ParseElementHtmlBlock.h"
#include "ParseElementCodeBlock.h"
#include "ParseElementCodeFence.h"
#include "ParseElementHeaderAtx.h"
#include "ParseElementHeaderSetext.h"
#include "ParseElementHorizontal.h"
#include "ParseElementListUnordered.h"
#include "ParseElementListOrdered.h"
#include "ParseElementQuote.h"
#include "ParseElementParagraph.h"
#include "ParseElementFactory.h"
#include "ParseElementSpan.h"
#include "ParseElementPlain.h"
#include "ParseElementEscape.h"
#include "ParseElementAmp.h"
#include "ParseElementCodeInline.h"
#include "ParseElementEmphasis.h"
#include "ParseElementStrong.h"
#include "ParseElementHtmlInline.h"
#include "ParseElementLinkInline.h"
#include "ParseElementLinkLabel.h"
#include "ParseElementLinkReference.h"
#include "ParseElementImageInline.h"
#include "ParseElementImageReference.h"
#include "ParseElementLinkAutomatic.h"

QSharedPointer<ParseElement> ParseElementFactory::copy(const QSharedPointer<ParseElement> element) const {
    ParseElement* newElement = nullptr;
    switch (element->type()) {
    case ParseElementType::TYPE_HTML_BLOCK:
        newElement = new ParseElementHtmlBlock(*qSharedPointerDynamicCast<ParseElementHtmlBlock>(element));
        break;
    case ParseElementType::TYPE_CODE_BLOCK:
        newElement = new ParseElementCodeBlock(*qSharedPointerDynamicCast<ParseElementCodeBlock>(element));
        break;
    case ParseElementType::TYPE_CODE_FENCE:
        newElement = new ParseElementCodeFence(*qSharedPointerDynamicCast<ParseElementCodeFence>(element));
        break;
    case ParseElementType::TYPE_HEADER_ATX:
        newElement = new ParseElementHeaderAtx(*qSharedPointerDynamicCast<ParseElementHeaderAtx>(element));
        break;
    case ParseElementType::TYPE_HEADER_SETEXT:
        newElement = new ParseElementHeaderSetext(*qSharedPointerDynamicCast<ParseElementHeaderSetext>(element));
        break;
    case ParseElementType::TYPE_HORIZON:
        newElement = new ParseElementHorizontal(*qSharedPointerDynamicCast<ParseElementHorizontal>(element));
        break;
    case ParseElementType::TYPE_LIST_UNORDERED:
        newElement = new ParseElementListUnordered(*qSharedPointerDynamicCast<ParseElementListUnordered>(element));
        break;
    case ParseElementType::TYPE_LIST_ORDERED:
        newElement = new ParseElementListOrdered(*qSharedPointerDynamicCast<ParseElementListOrdered>(element));
        break;
    case ParseElementType::TYPE_QUOTE:
        newElement = new ParseElementQuote(*qSharedPointerDynamicCast<ParseElementQuote>(element));
        break;
    case ParseElementType::TYPE_PARAGRAPH:
        newElement = new ParseElementParagraph(*qSharedPointerDynamicCast<ParseElementParagraph>(element));
        break;
    case ParseElementType::TYPE_PLAIN:
        newElement = new ParseElementPlain(*qSharedPointerDynamicCast<ParseElementPlain>(element));
        break;
    case ParseElementType::TYPE_AMP:
        newElement = new ParseElementAmp(*qSharedPointerDynamicCast<ParseElementAmp>(element));
        break;
    case ParseElementType::TYPE_ESCAPE:
        newElement = new ParseElementEscape(*qSharedPointerDynamicCast<ParseElementEscape>(element));
        break;
    case ParseElementType::TYPE_CODE_INLINE:
        newElement = new ParseElementCodeInline(*qSharedPointerDynamicCast<ParseElementCodeInline>(element));
        break;
    case ParseElementType::TYPE_EMPHASIS:
        newElement = new ParseElementEmphasis(*qSharedPointerDynamicCast<ParseElementEmphasis>(element));
        break;
    case ParseElementType::TYPE_STRONG:
        newElement = new ParseElementStrong(*qSharedPointerDynamicCast<ParseElementStrong>(element));
        break;
    case ParseElementType::TYPE_HTML_INLINE:
        newElement = new ParseElementHtmlInline(*qSharedPointerDynamicCast<ParseElementHtmlInline>(element));
        break;
    case ParseElementType::TYPE_LINK_INLINE:
        newElement = new ParseElementLinkInline(*qSharedPointerDynamicCast<ParseElementLinkInline>(element));
        break;
    case ParseElementType::TYPE_LINK_LABEL:
        newElement = new ParseElementLinkLabel(*qSharedPointerDynamicCast<ParseElementLinkLabel>(element));
        break;
    case ParseElementType::TYPE_LINK_REFERENCE:
        newElement = new ParseElementLinkReference(*qSharedPointerDynamicCast<ParseElementLinkReference>(element));
        break;
    case ParseElementType::TYPE_IMAGE_INLINE:
        newElement = new ParseElementImageInline(*qSharedPointerDynamicCast<ParseElementImageInline>(element));
        break;
    case ParseElementType::TYPE_IMAGE_REFERENCE:
        newElement = new ParseElementImageReference(*qSharedPointerDynamicCast<ParseElementImageReference>(element));
        break;
    case ParseElementType::TYPE_LINK_AUTOMATIC:
        newElement = new ParseElementLinkAutomatic(*qSharedPointerDynamicCast<ParseElementLinkAutomatic>(element));
        break;
    default:
        break;
    }
    return QSharedPointer<ParseElement>(newElement);
}

QSharedPointer<ParseElementBlock> ParseElementFactory::copy(const QSharedPointer<ParseElementBlock> element) const {
    return qSharedPointerDynamicCast<ParseElementBlock>(copy(qSharedPointerDynamicCast<ParseElement>(element)));
}

QSharedPointer<ParseElementSpan> ParseElementFactory::copy(const QSharedPointer<ParseElementSpan> element) const {
    return qSharedPointerDynamicCast<ParseElementSpan>(copy(qSharedPointerDynamicCast<ParseElement>(element)));
}
