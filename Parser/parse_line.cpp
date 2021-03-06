#include <algorithm>
#include "parse_elem.h"
#include "parse_elem_block.h"
#include "parse_elem_span.h"
#include "parse_elem_paragraph.h"
#include "parse_line.h"
using namespace std;

ParseLine::ParseLine() {
    this->_prev = nullptr;
    this->_next = nullptr;
    this->labelSet = nullptr;
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
    if (prevLine != nullptr) {
        prevLine->_next = this;
    }
    if (nextLine != nullptr) {
        nextLine->_prev = this;
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

void ParseLine::removeCurrentElements() {
    this->removeCurrentBlocks();
    this->removeCurrentSpans();
}

void ParseLine::removeCurrentBlocks() {
    for (auto block : this->blocks) {
        block->remove();
    }
    this->blocks.clear();
}

void ParseLine::removeCurrentSpans() {
    for (auto span : this->spans) {
        span->remove();
    }
    this->spans.clear();
}

void ParseLine::saveLineStatus() {
    this->_oldBlocks = this->blocks;
}

bool ParseLine::isLineStatusChanged() const {
    if (this->_oldBlocks.size() != this->blocks.size()) {
        return true;
    }
    int len = this->blocks.size();
    for (int i = 0; i < len; ++i) {
        if (this->_oldBlocks[i]->type() != this->blocks[i]->type() ||
            this->_oldBlocks[i]->offset != this->blocks[i]->offset) {
            return true;
        }
    }
    return false;
}

string ParseLine::generateHtml() const {
    string html;
    vector<OffsetElement> orders;
    for (auto span : spans) {
        OffsetElement order;
        order.elem = span;
        order.offset = span->utf8Offset;
        order.isOpen = true;
        orders.push_back(order);
        order.offset = span->utf8Offset + span->utf8Length - 1;
        order.isOpen = false;
        orders.push_back(order);
    }
    sort(orders.begin(), orders.end());
    for (auto it = blocks.begin(); it != blocks.end(); ++it) {
        shared_ptr<ParseElement> element(*it);
        html += dynamic_pointer_cast<ParseElementBlock>(element)->generateOpenHtml();
    }
    for (auto order : orders) {
        if (order.isOpen) {
            if (order.elem->openActivate) {
                html += order.elem->generateOpenHtml();
            }
        }
        else {
            if (order.elem->closeActivate) {
                html += order.elem->generateCloseHtml();
            }
        }
    }
    for (auto it = blocks.rbegin(); it != blocks.rend(); ++it) {
        shared_ptr<ParseElement> element(*it);
        html += dynamic_pointer_cast<ParseElementBlock>(element)->generateCloseHtml();
    }
    return html;
}

shared_ptr<ParseElement> ParseLine::getElementAt(const int offset) const {
    for (auto element : this->blocks) {
        if (element->offset == offset) {
            return element;
        } else if (element->offset > offset) {
            break;
        }
    }
    return nullptr;
}

ParseElementType ParseLine::getTypeAt(const int offset) const {
    auto element = getElementAt(offset);
    if (element == nullptr) {
        return ParseElementType::TYPE_INVALID;
    }
    return element->type();
}

int ParseLine::getIndexAt(const int offset) const {
    int len = this->blocks.size();
    for (int i = 0; i < len; ++i) {
        if (blocks[i]->offset == offset) {
            return i;
        } else if (blocks[i]->offset > offset) {
            break;
        }
    }
    return -1;
}
