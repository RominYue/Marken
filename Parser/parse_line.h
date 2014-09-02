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
class ParseElementBlock;
class ParseElementSpan;
class ParseLabelSet;

class ParseLine {
public:
    ParseLine();
    virtual ~ParseLine();

    ParseLine* prev() const;
    ParseLine* next() const;
    void setNeighbor(ParseLine* prevLine, ParseLine* nextLine);
    void removeFromList();

    void removeCurrentElements();
    void removeCurrentBlocks();
    void removeCurrentSpans();
    void saveLineStatus();
    bool isLineStatusChanged() const;

    string generateHtml() const;

    shared_ptr<ParseElement> getElementAt(const int offset) const;
    ParseElementType getTypeAt(const int offset) const;
    int getIndexAt(const int offset) const;

    ParseLabelSet* labelSet;
    vector<shared_ptr<ParseElementBlock>> blocks;
    vector<shared_ptr<ParseElementSpan>> spans;

private:
    ParseLine* _prev;
    ParseLine* _next;
    vector<shared_ptr<ParseElementBlock>> _oldBlocks;
    vector<shared_ptr<ParseElementBlock>> _oldSpans;

    struct OffsetElement {
        shared_ptr<ParseElementSpan> elem;
        int offset;
        bool isOpen;
        bool operator <(const OffsetElement& element) const {
            if (offset == element.offset) {
                return isOpen > element.isOpen;
            }
            return offset < element.offset;
        }
    };
};

#endif // PARSE_LINE_H_INCLUDED
