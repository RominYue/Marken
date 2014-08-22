#ifndef MARKDOWNDEFINATION_H
#define MARKDOWNDEFINATION_H

#include <QString>

class MarkdownDefination
{
public:
    enum SyntaxType {
        DEFAULT,
        BLOCK_HTML,
        SPAN_HTML,
        ATX_HEADER_1,
        ATX_HEADER_2,
        ATX_HEADER_3,
        ATX_HEADER_4,
        ATX_HEADER_5,
        ATX_HEADER_6,
        SETEX_HEADER_1,
        SETEX_HEADER_2,
        HORIZONTAL,
        BLOCK_QUOTE,
        UNORDERED_LIST,
        ORDERED_LIST,
        CODE_BLOCK,
        INLINE_LINK,
        REFERENCE_LINK,
        LINK_LABEL,
        EMPHASIS,
        STRONG,
        IMAGE,
        INLINE_CODE,
    };
    static QString getString(SyntaxType type);
};

#endif // MARKDOWNDEFINATION_H
