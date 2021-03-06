#ifndef PARSE_ELEM_TYPE_H_INCLUDED
#define PARSE_ELEM_TYPE_H_INCLUDED

#define UNUSED(x) (void)(x)

enum class ParseElementType {
    TYPE_INVALID,
    TYPE_EMPTY,

    TYPE_HTML_BLOCK,
    TYPE_CODE_BLOCK,
    TYPE_HEADER_ATX,
    TYPE_HEADER_SETEXT,
    TYPE_HORIZON,
    TYPE_QUOTE,
    TYPE_LIST_UNORDERED,
    TYPE_LIST_ORDERED,
    TYPE_PARAGRAPH,

    TYPE_PLAIN,
    TYPE_ESCAPE,
    TYPE_AMP,
    TYPE_HTML_INLINE,
    TYPE_CODE_INLINE,
    TYPE_EMPHASIS,
    TYPE_STRONG,
    TYPE_IMAGE_INLINE,
    TYPE_IMAGE_REFERENCE,
    TYPE_LINK_INLINE,
    TYPE_LINK_REFERENCE,
    TYPE_LINK_LABEL,
    TYPE_LINK_AUTOMATIC,
};

#endif // PARSE_ELEM_TYPE_H_INCLUDED
