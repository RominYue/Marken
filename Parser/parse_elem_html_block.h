#ifndef PARSE_ELEM_HTML_BLOCK_H
#define PARSE_ELEM_HTML_BLOCK_H

#include <set>
using std::set;
#include "parse_elem_html.h"
#include "parse_elem_block.h"

class ParseElementHtmlBlock : public ParseElementBlock, public ParseElementHtml {
public:
    ParseElementHtmlBlock();
    virtual ParseElementType type() const;

    virtual bool tryParse(const string &line, int offset, int& length) override;
    virtual string generateOpenHtml() const override final;
};

#endif // PARSE_ELEM_HTML_BLOCK_H
