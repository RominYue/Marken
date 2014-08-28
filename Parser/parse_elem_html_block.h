#ifndef PARSE_ELEM_HTML_BLOCK_H
#define PARSE_ELEM_HTML_BLOCK_H

#include "parse_elem_block.h"

class ParseElementHtmlBlock : public ParseElementBlock {
public:
    ParseElementHtmlBlock();
    virtual ParseElementType type() const;

    const string& tag() const;
    void setTag(const string& val);

    virtual bool tryParse(const string &line, int offset, int& length) override;
    virtual string generateOpenHtml() const override final;

private:
    enum Status {
        STATUS_BEGIN,
        STATUS_LT,
        STATUS_SLASH,
        STATUS_TAG,
        STATUS_SPACE_SUF,
        STATUS_GT
    };
    string _tag;
    bool findOpenTagOffset(const string &line, int &index);
    bool findCloseTagOffset(const string &line, int &index);
    bool matchToEnd(const string &line, int &index);
};

#endif // PARSE_ELEM_HTML_BLOCK_H
