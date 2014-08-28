#ifndef PARSE_ELEM_TYPE_H_INCLUDED
#define PARSE_ELEM_TYPE_H_INCLUDED

enum class ParseElementType {
    TYPE_INVALID,

    TYPE_HTML_BLOCK,
    TYPE_HTML_BLOCK_END,

    TYPE_HEADER, TYPE_HORIZON,
    TYPE_LIST_ORDERED, TYPE_LIST_UNORDERED,
    TYPE_BLOCK_QUOTE, TYPE_CODE_BLOCK,
    TYPE_PARAGRAPH,
};

#endif // PARSE_ELEM_TYPE_H_INCLUDED
