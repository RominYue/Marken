#ifndef PARSE_ELEM_FACTORY_H
#define PARSE_ELEM_FACTORY_H

class ParseElement;

class ParseElementFactory {
public:
    ParseElementFactory() = default;
    virtual ~ParseElementFactory() = default;
    shared_ptr<ParseElement> copy(const shared_ptr<ParseElement> element) const;
};

#endif // PARSE_ELEM_FACTORY_H
