#include "parse_line.h"
#include "parse_elem_paragraph.h"
using namespace std;

ParseElementParagraph::ParseElementParagraph() : ParseElementBlock() {
}

ParseElementType ParseElementParagraph::type() const {
    return ParseElementType::TYPE_PARAGRAPH;
}

bool ParseElementParagraph::tryParse(const string &line, int offset, int& length) {
    this->isVirtual = false;
    if (line[offset] != ' ' && line[offset] != '\t') {
        length = line.length() - offset;
        text = "";
        return true;
    }
    return false;
}

string ParseElementParagraph::generateOpenHtml() const {
    int elemLen = parent->elements.size();
    if (elemLen > 1) {
        auto prevElem = parent->elements[elemLen - 2];
        if (prevElem->isBlockElement()) {
            auto prevBlock = dynamic_pointer_cast<ParseElementBlock>(prevElem);
            if (!prevBlock->isVirtual) {
                if (prevBlock->type() == ParseElementType::TYPE_LIST_ORDERED ||
                    prevBlock->type() == ParseElementType::TYPE_LIST_UNORDERED) {
                    return "<p>";
                }
            }
        }
    }
    if (parent->prev() == nullptr) {
        return "<p>";
    }
    return "<p>";
}

string ParseElementParagraph::generateCloseHtml() const {
    return "</p>";
}
