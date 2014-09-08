#ifndef PARSE_ELEM_FACTORY_H
#define PARSE_ELEM_FACTORY_H

#include <QSharedPointer>

class ParseElement;
class ParseElementBlock;
class ParseElementSpan;

class ParseElementFactory {
public:
    ParseElementFactory() = default;
    virtual ~ParseElementFactory() = default;
    QSharedPointer<ParseElement> copy(const QSharedPointer<ParseElement> element) const;
    QSharedPointer<ParseElementBlock> copy(const QSharedPointer<ParseElementBlock> element) const;
    QSharedPointer<ParseElementSpan> copy(const QSharedPointer<ParseElementSpan> element) const;
};

#endif // PARSE_ELEM_FACTORY_H
