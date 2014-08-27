#ifndef PARSE_ELEM_H_INCLUDED
#define PARSE_ELEM_H_INCLUDED

#include <string>
#include <memory>
#include "parse_type.h"

class ParseLineData;

class ParseElem {
public:
    ParseElem();
    virtual ~ParseElem();
    ParseElem(const ParseElem&) = default;
    ParseElem& operator=(const ParseElem&) = default;

    int indent() const;
    void setIndent(const int val);
    int length() const;
    void setLength(const int val);
    const std::string& text() const;
    void setText(const std::string& val);
    ParseLineData* parent() const;
    void setParent(ParseLineData* val);

    virtual ParseElemType type() const;
    virtual bool isBlockElement() const = 0;

    virtual bool isEqual(const std::shared_ptr<ParseElem> elem) const;

    virtual bool tryParse(std::string text, int offset, int &len);

protected:
    int _indent;
    int _length;
    std::string _text;
    ParseLineData *_parent;
};

#endif // PARSE_ELEM_H_INCLUDED
