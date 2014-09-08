#ifndef PARSE_ELEM_LINK_INLINE_H
#define PARSE_ELEM_LINK_INLINE_H

#include "ParseElementSpan.h"
#include "ParseElementLink.h"

class ParseElementLinkInline : public ParseElementSpan, public ParseElementLink {
public:
    ParseElementLinkInline();
    virtual ~ParseElementLinkInline() = default;
    virtual ParseElementType type() const override final;

    virtual qint32 tryParse(const QString& text, qint32 offset) override final;
    virtual QString generateOpenHtml() const override final;
    virtual QString generateCloseHtml() const override final;

    virtual QString innerText() const override final;
    virtual qint32 innerOffset() const override final;

private:
    QString _inner;
    QString _help;
    QString _link;
    QString _title;
};

#endif // PARSE_ELEM_LINK_INLINE_H