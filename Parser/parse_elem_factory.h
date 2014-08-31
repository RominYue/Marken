#ifndef PARSE_ELEM_FACTORY_H
#define PARSE_ELEM_FACTORY_H

class ParseElement;
class ParseElementBlock;
class ParseElementSpan;

class ParseElementFactory {
public:
    ParseElementFactory() = default;
    virtual ~ParseElementFactory() = default;
    shared_ptr<ParseElement> copy(const shared_ptr<ParseElement> element) const;
    shared_ptr<ParseElementBlock> copy(const shared_ptr<ParseElementBlock> element) const;
    shared_ptr<ParseElementSpan> copy(const shared_ptr<ParseElementSpan> element) const;
};

#endif // PARSE_ELEM_FACTORY_H
