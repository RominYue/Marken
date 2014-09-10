#ifndef PARSE_ELEM_LINK_REFERENCE_H
#define PARSE_ELEM_LINK_REFERENCE_H

#include "ParseElementSpan.h"
#include "ParseElementLink.h"

class ParseElementLinkReference : public ParseElementSpan, public ParseElementLink {
public:
    ParseElementLinkReference();
    virtual ~ParseElementLinkReference() = default;
    virtual ParseElementType type() const override final;

    virtual QString innerText() const override final;
    virtual int innerOffset() const override final;

    virtual int tryParse(const QString& text, int offset) override final;
    virtual QString generateOpenHtml() const override final;
    virtual QString generateCloseHtml() const override final;

private:
    QString _inner;
    QString _label;
};

#endif // PARSE_ELEM_LINK_REFERENCE_H
