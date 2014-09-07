#include "parse_line.h"
#include "parse_elem_quote.h"
using namespace std;

ParseElementQuote::ParseElementQuote() : ParseElementBlock() {
}

ParseElementType ParseElementQuote::type() const {
    return ParseElementType::TYPE_QUOTE;
}

bool ParseElementQuote::tryParse(const string &line, int offset, int& length) {
    int lineLen = line.length();
    if (lineLen > offset) {
        if (line[offset] == ' ' || line[offset] == '\t') {
            if (parent->prev() == nullptr) {
                return false;
            }
            if (parent->prev()->getTypeAt(offset) == ParseElementType::TYPE_LIST_UNORDERED) {
                this->isVirtual = true;
                length = 1;
                return true;
            }
        } else if (line[offset] == '>') {
            if (offset + 1 == lineLen || line[offset + 1] == ' ' || line[offset + 1] == '\t') {
                this->isVirtual = false;
                length = 1;
                return true;
            }
        }
    }
    return false;
}

bool ParseElementQuote::inheritable() const {
    return true;
}

string ParseElementQuote::generateOpenHtml() const {
    if (parent->prev() == nullptr) {
        return "<blockquote>";
    }
    if (parent->prev()->getTypeAt(offset) != ParseElementType::TYPE_QUOTE) {
        return "<blockquote>";
    }
    return "";
}

string ParseElementQuote::generateCloseHtml() const {
    if (parent->next() == nullptr) {
        return "</blockquote>";
    }
    if (parent->next()->getTypeAt(offset) != ParseElementType::TYPE_QUOTE) {
        return "</blockquote>";
    }
    return "";
}
