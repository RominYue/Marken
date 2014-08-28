#ifndef PARSE_LINE_H_INCLUDED
#define PARSE_LINE_H_INCLUDED

#include <vector>
#include <string>
#include <memory>
#include "parse_elem_type.h"
using std::vector;
using std::string;
using std::shared_ptr;

class ParseElement;

class ParseLine {
public:
    ParseLine();
    virtual ~ParseLine();

    ParseLine* prev() const;
    ParseLine* next() const;
    void setNeighbor(ParseLine* prevLine, ParseLine* nextLine);
    void removeFromList();

    void saveLineStatus();
    bool isLineStatusChanged() const;

    string generateHtml() const;

    shared_ptr<ParseElement> getElementAt(const int offset);
    ParseElementType getTypeAt(const int offset);

    vector<shared_ptr<ParseElement>> elements;

private:
    ParseLine* _prev;
    ParseLine* _next;
    vector<shared_ptr<ParseElement>> _oldElements;
};

#endif // PARSE_LINE_H_INCLUDED
