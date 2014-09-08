#ifndef PARSE_ELEM_PARAGRAPH_H
#define PARSE_ELEM_PARAGRAPH_H

#include "ParseElementBlock.h"

class ParseElementParagraph : public ParseElementBlock {
public:
    ParseElementParagraph();
    virtual ~ParseElementParagraph() = default;
    virtual ParseElementType type() const;

    virtual bool stopParsing(qint32 offset) const override final;
    virtual bool tryParse(const QString &line, qint32 offset, qint32& length) override;
    virtual QString generateOpenHtml() const override final;
    virtual QString generateCloseHtml() const override final;

    bool isParagraphBegin() const;
    bool isParagraphEnd() const;
private:
    bool isListSingleLine() const;
};

#endif // PARSE_ELEM_PARAGRAPH_H