#ifndef PARSE_ELEM_HTML_BLOCK_H
#define PARSE_ELEM_HTML_BLOCK_H

#include <set>
using std::set;
#include "ParseElementHtml.h"
#include "ParseElementBlock.h"

class ParseElementHtmlBlock : public ParseElementBlock, public ParseElementHtml {
public:
    ParseElementHtmlBlock();
    virtual ~ParseElementHtmlBlock() = default;
    virtual ParseElementType type() const;

    virtual bool tryParse(const QString &line, qint32 offset, qint32& length) override;
    virtual QString generateOpenHtml() const override final;
};

#endif // PARSE_ELEM_HTML_BLOCK_H
