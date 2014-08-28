#include "parse_elem.h"
#include "parse_elem_block.h"
#include "parse_elem_span.h"
#include "parse_elem_paragraph.h"
#include "parse_line.h"
using namespace std;

ParseLine::ParseLine() {
    this->_prev = nullptr;
    this->_next = nullptr;
}

ParseLine::~ParseLine() {
    this->removeFromList();
}

ParseLine* ParseLine::prev() const {
    return this->_prev;
}

ParseLine* ParseLine::next() const {
    return this->_next;
}

void ParseLine::setNeighbor(ParseLine* prevLine, ParseLine* nextLine) {
    this->_prev = prevLine;
    this->_next = nextLine;
    if (this->_prev != nullptr) {
        this->_prev->_next = this;
    }
    if (this->_next != nullptr) {
        this->_next->_prev = this;
    }
}

void ParseLine::removeFromList() {
    if (this->_prev != nullptr) {
        this->_prev->_next = this->_next;
    }
    if (this->_next != nullptr) {
        this->_next->_prev = this->_prev;
    }
    this->_prev = nullptr;
    this->_next = nullptr;
}

void ParseLine::saveLineStatus() {
    this->_oldElements = this->elements;
}

bool ParseLine::isLineStatusChanged() const {
    if (this->_oldElements.size() != this->elements.size()) {
        return true;
    }
    int len = this->elements.size();
    for (int i = 0; i < len; ++i) {
        if (!(this->_oldElements[i] == this->elements[i])) {
            return true;
        }
    }
    return false;
}

string ParseLine::generateHtml() const {
    string html;
    for (auto it = elements.begin(); it != elements.end(); ++it) {
        shared_ptr<ParseElement> element(*it);
        if (element->isBlockElement()) {
            html += dynamic_pointer_cast<ParseElementBlock>(element)->generateOpenHtml();
        } else {
            html += dynamic_pointer_cast<ParseElementSpan>(element)->generateHtml();
        }
    }
    for (auto it = elements.rbegin(); it != elements.rend(); ++it) {
        shared_ptr<ParseElement> element(*it);
        if (element->isBlockElement()) {
            html += dynamic_pointer_cast<ParseElementBlock>(element)->generateCloseHtml();
        }
    }
    return html;
}

shared_ptr<ParseElement> ParseLine::getElementAt(const int offset) {
    for (auto element : this->elements) {
        if (element->offset == offset) {
            return element;
        } else if (element->offset > offset) {
            break;
        }
    }
    return nullptr;
}

ParseElementType ParseLine::getTypeAt(const int offset) {
    auto element = getElementAt(offset);
    if (element == nullptr) {
        return ParseElementType::TYPE_INVALID;
    }
    return element->type();
}
