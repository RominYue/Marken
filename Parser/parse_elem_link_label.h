#ifndef PARSE_ELEM_LINK_LABEL_H
#define PARSE_ELEM_LINK_LABEL_H

#include "parse_elem_block.h"
#include "parse_elem_link.h"

class ParseElementLinkLabel : public ParseElementBlock, public ParseElementLink {
public:
    ParseElementLinkLabel();
    virtual ParseElementType type() const override final;

    virtual bool tryParse(const string &line, int offset, int& length) override final;

    virtual void remove() override final;

    string label;
    string link;
    string title;

    bool isBegin;

private:
    void addToLabelSet();
};

#endif // PARSE_ELEM_LINK_LABEL_H
