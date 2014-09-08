#ifndef PARSE_ELEM_LINK_LABEL_H
#define PARSE_ELEM_LINK_LABEL_H

#include "ParseElementBlock.h"
#include "ParseElementLink.h"

class ParseElementLinkLabel : public ParseElementBlock, public ParseElementLink {
public:
    ParseElementLinkLabel();
    virtual ~ParseElementLinkLabel() = default;
    virtual ParseElementType type() const override final;

    virtual bool tryParse(const QString &line, qint32 offset, qint32& length) override final;

    virtual void remove() override final;

    QString label;
    QString link;
    QString title;

    bool isBegin;

private:
    void addToLabelSet();
};

#endif // PARSE_ELEM_LINK_LABEL_H
