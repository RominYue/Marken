#ifndef PARSE_ELEM_H_INCLUDED
#define PARSE_ELEM_H_INCLUDED

#include <QString>
#include "ParseElementType.h"

class ParseLineData;

class ParseElement {
public:
    ParseElement();
    virtual ~ParseElement() = default;

    virtual ParseElementType type() const;
    virtual bool isBlockElement() const;

    virtual QString generateOpenHtml() const;
    virtual QString generateCloseHtml() const;

    virtual QString innerText() const;
    virtual qint32 innerOffset() const;

    virtual void remove();

    qint32 offset;
    qint32 length;
    QString text;
    ParseLineData* parent;

protected:
    QString removeSideSpaces(const QString& text) const;
    QString htmlEscaped(const QString& text) const;
};

#endif // PARSE_ELEM_H_INCLUDED
