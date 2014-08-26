#ifndef PARSE_ELEM_H_INCLUDED
#define PARSE_ELEM_H_INCLUDED

#include <string>
#include <memory>
#include "parse_type.h"

/**
 * Parse elements include the text blocks which could translated to an HTML tag,
 * the text blocks which could translate to plain text,
 * and the hidden closed HTML tags in the end of line.
 */
class ParseElem {
public:
    ParseElem();
    virtual ~ParseElem();
    int indent() const;
    void setIndent(const int indent);
    ParseElemType type() const;
    void setType(const ParseElemType type);
    const std::string& text() const;
    void setText(const std::string& val);

    virtual bool isEqual(const std::shared_ptr<ParseElem> elem) const;
    virtual std::string generateHtml() const;

protected:
    int _indent; /**< Indent is the start position of the element in the line. */
    ParseElemType _type;
    std::string _text;
};

#endif // PARSE_ELEM_H_INCLUDED
