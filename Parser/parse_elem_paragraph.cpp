#include "parse_line.h"
#include "parse_elem_list_ordered.h"
#include "parse_elem_list_unordered.h"
#include "parse_elem_quote.h"
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
        if (parent->prev() != nullptr) {
            if (parent->prev()->blocks.size() > 0) {
                auto lastElem = (*parent->prev()->blocks.rbegin());
                if (lastElem->type() == ParseElementType::TYPE_EMPTY) {
                } else if (parent->prev()->getTypeAt(offset) == ParseElementType::TYPE_LIST_ORDERED) {
                    shared_ptr<ParseElementListOrdered> elem(new ParseElementListOrdered());
                    elem->isVirtual = true;
                    elem->offset = offset;
                    elem->utf8Offset = 0;
                    elem->utf8Length = 0;
                    elem->parent = this->parent;
                    this->parent->blocks.push_back(dynamic_pointer_cast<ParseElementBlock>(elem));
                } else if (parent->prev()->getTypeAt(offset) == ParseElementType::TYPE_LIST_UNORDERED) {
                    shared_ptr<ParseElementListUnordered> elem(new ParseElementListUnordered());
                    elem->isVirtual = true;
                    elem->offset = offset;
                    elem->utf8Offset = 0;
                    elem->utf8Length = 0;
                    elem->parent = this->parent;
                    this->parent->blocks.push_back(dynamic_pointer_cast<ParseElementBlock>(elem));
                } else if (parent->prev()->getTypeAt(offset) == ParseElementType::TYPE_QUOTE) {
                    shared_ptr<ParseElementQuote> elem(new ParseElementQuote());
                    elem->isVirtual = true;
                    elem->offset = offset;
                    elem->utf8Offset = 0;
                    elem->utf8Length = 0;
                    elem->parent = parent;
                    elem->parent = this->parent;
                    this->parent->blocks.push_back(dynamic_pointer_cast<ParseElementBlock>(elem));
                }
            }
        }
        int elemLen = parent->blocks.size();
        if (elemLen == 0) {
            this->offset = 0;
        } else {
            auto elem = *parent->blocks.rbegin();
            int elemOffset = elem->offset;
            this->offset = offset;
            if (parent->prev() != nullptr) {
                if (parent->prev()->blocks.size() == parent->blocks.size() + 1) {
                    if (parent->prev()->getTypeAt(elemOffset) == elem->type()) {
                        auto prevElem = (*parent->prev()->blocks.rbegin());
                        if (prevElem->type() == ParseElementType::TYPE_PARAGRAPH) {
                            this->offset = prevElem->offset;
                        }
                    }
                }
            }
        }
        length = line.length() - offset;
        return true;
    }
    return false;
}

string ParseElementParagraph::generateOpenHtml() const {
    if (isListSingleLine()) {
        return "";
    }
    if (this->isParagraphBegin()) {
        return "<p>";
    }
    return "";
}

string ParseElementParagraph::generateCloseHtml() const {
    if (isListSingleLine()) {
        return "";
    }
    if (this->isParagraphEnd()) {
        return "</p>";
    }
    return "";
}

bool ParseElementParagraph::isParagraphBegin() const {
    if (parent->prev() == nullptr) {
        return true;
    }
    if (parent->prev()->getTypeAt(offset) != ParseElementType::TYPE_PARAGRAPH) {
        return true;
    }
    int elemLen = parent->blocks.size();
    if (elemLen > 1) {
        auto prevElem = parent->blocks[elemLen - 2];
        if (prevElem->isBlockElement()) {
            auto prevBlock = dynamic_pointer_cast<ParseElementBlock>(prevElem);
            if (!prevBlock->isVirtual) {
                if (prevBlock->type() == ParseElementType::TYPE_LIST_ORDERED ||
                    prevBlock->type() == ParseElementType::TYPE_LIST_UNORDERED) {
                    return true;
                }
            }
        }
    }
    return false;
}

bool ParseElementParagraph::isParagraphEnd() const {
    if (parent->next() == nullptr) {
        return true;
    }
    if (parent->next()->getTypeAt(offset) != ParseElementType::TYPE_PARAGRAPH) {
        return true;
    }
    int elemLen = parent->blocks.size();
    if (elemLen > 1) {
        auto prevElem = parent->blocks[elemLen - 2];
        if (prevElem->isBlockElement()) {
            auto prevBlock = dynamic_pointer_cast<ParseElementBlock>(prevElem);
            if (!prevBlock->isVirtual) {
                if (prevBlock->type() == ParseElementType::TYPE_LIST_ORDERED ||
                    prevBlock->type() == ParseElementType::TYPE_LIST_UNORDERED) {
                    if (parent->next()->getTypeAt(prevElem->offset) != prevElem->type()) {
                        return true;
                    }
                    auto nextElem = parent->next()->getElementAt(prevElem->offset);
                    if (nextElem->isBlockElement()) {
                        auto nextBlock = dynamic_pointer_cast<ParseElementBlock>(nextElem);
                        if (!nextBlock->isVirtual) {
                            return true;
                        }
                    }
                }
            }
        }
    }
    return false;
}

bool ParseElementParagraph::isListSingleLine() const {
    int elemLen = parent->blocks.size();
    if (elemLen > 1) {
        auto prevElem = parent->blocks[elemLen - 2];
        if (prevElem->isBlockElement()) {
            auto prevBlock = dynamic_pointer_cast<ParseElementBlock>(prevElem);
            if (!prevBlock->isVirtual) {
                if (prevBlock->type() == ParseElementType::TYPE_LIST_ORDERED ||
                    prevBlock->type() == ParseElementType::TYPE_LIST_UNORDERED) {
                    ParseLine* line = this->parent;
                    while (true) {
                        ParseLine* next = line->next();
                        if (next == nullptr) {
                            return true;
                        }
                        if (next->blocks.size() != line->blocks.size()) {
                            return true;
                        }
                        int blockLen = next->blocks.size();
                        for (int i = 0; i < blockLen - 1; ++i) {
                            if (next->blocks[i]->type() != line->blocks[i]->type()) {
                                return true;
                            }
                            if (next->blocks[i]->offset != line->blocks[i]->offset) {
                                return true;
                            }
                            if (i < blockLen - 2) {
                                if (next->blocks[i]->isVirtual != line->blocks[i]->isVirtual) {
                                    return true;
                                }
                            }
                        }
                        if (next->blocks[blockLen - 2]->isVirtual == false) {
                            return true;
                        }
                        if (next->blocks[blockLen - 1]->type() == ParseElementType::TYPE_PARAGRAPH) {
                            return false;
                        }
                        line = next;
                    }
                }
            }
        }
    }
    return false;
}
