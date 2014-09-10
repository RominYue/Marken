#ifndef PARSE_ELEM_IMAGE_REFERENCE_H
#define PARSE_ELEM_IMAGE_REFERENCE_H

#include "ParseElementImage.h"

class ParseElementImageReference : public ParseElementImage{
public:
    ParseElementImageReference();
    virtual ~ParseElementImageReference() = default;
    virtual ParseElementType type() const override final;

    virtual int tryParse(const QString& text, int offset) override final;
    virtual QString generateOpenHtml() const override final;

private:
    QString _label;
};

#endif // PARSE_ELEM_IMAGE_REFERENCE_H
