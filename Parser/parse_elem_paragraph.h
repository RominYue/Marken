#ifndef PARSE_ELEM_PARAGRAPH_H
#define PARSE_ELEM_PARAGRAPH_H

#include "parse_elem_block.h"

class ParseElementParagraph : public ParseElementBlock {
public:
    ParseElementParagraph();
    virtual ParseElementType type() const;

    virtual bool stopParsing(int offset) const override final;
    virtual bool tryParse(const string &line, int offset, int& length) override;
    virtual string generateOpenHtml() const override final;
    virtual string generateCloseHtml() const override final;

    bool isParagraphBegin() const;
    bool isParagraphEnd() const;
private:
    bool isListSingleLine() const;
};

#endif // PARSE_ELEM_PARAGRAPH_H
