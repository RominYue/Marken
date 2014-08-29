#include "parse_line.h"
#include "parse_elem_header_setext.h"
using namespace std;

ParseElementHeaderSetext::ParseElementHeaderSetext() : ParseElementHeader() {
}

ParseElementType ParseElementHeaderSetext::type() const {
    return ParseElementType::TYPE_HEADER_SETEXT;
}

bool ParseElementHeaderSetext::tryParse(const string &line, int offset, int& length) {
    if (parent->prev() == nullptr) {
        return false;
    }
    if (parent->prev()->getTypeAt(offset) != ParseElementType::TYPE_PARAGRAPH) {
        return false;
    }
    if (parent->prev()->prev() != nullptr) {
        if (parent->prev()->prev()->getTypeAt(offset) == ParseElementType::TYPE_PARAGRAPH) {
            return false;
        }
    }
    int lineLen = line.length();
    if (lineLen > offset) {
        char ch = line[offset];
        if (ch == '=' || ch == '-') {
            for (int i = offset + 1; i < lineLen; ++i) {
                if (line[i] != ch) {
                    return false;
                }
            }
            if (ch == '=') {
                level = 1;
            } else {
                level = 2;
            }
            this->_isLower = true;
            int index = parent->getIndexAt(offset);
            auto elem = parent->prev()->elements[index];
            shared_ptr<ParseElementHeaderSetext> setext;
            setext->offset = elem->offset;
            setext->utf8Offset = elem->utf8Offset;
            setext->utf8Length = elem->utf8Length;
            setext->text = elem->text;
            setext->_isLower = false;
            parent->prev()->elements[index] = dynamic_pointer_cast<ParseElement>(setext);
            return true;
        }
    }
    return false;
}

string ParseElementHeaderSetext::generateOpenHtml() const {
    if (this->_isLower) {
        return "<hr>";
    }
    return this->generateOpenTag() + this->getCleanedHeader();
}

string ParseElementHeaderSetext::generateCloseHtml() const {
    if (this->_isLower) {
        return "";
    }
    return this->generateCloseTag();
}
