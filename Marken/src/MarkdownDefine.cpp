#include "MarkdownDefine.h"

QString MarkdownDefine::getString(SyntaxType type) {
    switch (type) {
    case DEFAULT:
        return "Default";
    case BLOCK_HTML:
        return "Block HTML";
    case SPAN_BEGIN_HTML:
        return "Span HTML";
    case SPAN_END_HTML:
        return "Span HTML";
    case ATX_HEADER_1:
        return "Atx Header 1";
    case ATX_HEADER_2:
        return "Atx Header 2";
    case ATX_HEADER_3:
        return "Atx Header 3";
    case ATX_HEADER_4:
        return "Atx Header 4";
    case ATX_HEADER_5:
        return "Atx Header 5";
    case ATX_HEADER_6:
        return "Atx Header 6";
    case SETEXT_HEADER_1:
        return "Setext Header 1";
    case SETEXT_HEADER_2:
        return "Setext Header 2";
    case HORIZONTAL:
        return "Horizontal";
    case BLOCK_QUOTE:
        return "Block Quote";
    case UNORDERED_LIST:
        return "Unordered List";
    case ORDERED_LIST:
        return "Ordered List";
    case CODE_BLOCK:
        return "Code Block";
    case INLINE_LINK:
        return "Inline Link";
    case REFERENCE_LINK:
        return "Reference Link";
    case LINK_LABEL:
        return "Link Label";
    case EMPHASIS:
        return "Emphasis";
    case STRONG:
        return "Strong";
    case IMAGE:
        return "Image";
    case INLINE_CODE:
        return "Inline Code";
    }
    return "";
}
