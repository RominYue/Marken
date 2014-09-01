#ifndef PARSE_ELEM_HTML_BLOCK_H
#define PARSE_ELEM_HTML_BLOCK_H

#include "parse_elem_html.h"
#include "parse_elem_block.h"

class ParseElementHtmlBlock : public ParseElementBlock, public ParseElementHtml {
public:
    ParseElementHtmlBlock();
    virtual ParseElementType type() const;

    virtual bool tryParse(const string &line, int offset, int& length) override;
    virtual bool inheritable() const override final;
    virtual string generateOpenHtml() const override final;

    bool isVirtual;
};

#endif // PARSE_ELEM_HTML_BLOCK_H
