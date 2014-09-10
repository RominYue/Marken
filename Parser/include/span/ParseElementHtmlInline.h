#ifndef PARSE_ELEM_HTML_INLINE_H
#define PARSE_ELEM_HTML_INLINE_H

#include "ParseElementHtml.h"
#include "ParseElementSpan.h"

class ParseElementHtmlInline : public ParseElementSpan, public ParseElementHtml {
public:
    ParseElementHtmlInline();
    virtual ~ParseElementHtmlInline() = default;
    virtual ParseElementType type() const override final;

    virtual int tryParse(const QString& text, int offset) override final;
    virtual QString generateOpenHtml() const override final;
};

#endif // PARSE_ELEM_HTML_INLINE_H
