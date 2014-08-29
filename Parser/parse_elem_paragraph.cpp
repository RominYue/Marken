#include "parse_line.h"
#include "parse_elem_list_ordered.h"
#include "parse_elem_list_unordered.h"
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
            if (parent->prev()->getTypeAt(offset) == ParseElementType::TYPE_LIST_ORDERED) {
                shared_ptr<ParseElementListOrdered> elem(new ParseElementListOrdered());
                elem->isVirtual = true;
                elem->offset = offset;
                elem->utf8Offset = 0;
                elem->utf8Length = 0;
				elem->parent = this->parent;
                this->parent->elements.push_back(dynamic_pointer_cast<ParseElementBlock>(elem));
            } else if (parent->prev()->getTypeAt(offset) == ParseElementType::TYPE_LIST_UNORDERED) {
                shared_ptr<ParseElementListUnordered> elem(new ParseElementListUnordered());
                elem->isVirtual = true;
                elem->offset = offset;
                elem->utf8Offset = 0;
				elem->utf8Length = 0;
				elem->parent = this->parent;
                this->parent->elements.push_back(dynamic_pointer_cast<ParseElementBlock>(elem));
            }
        }
		int elemLen = parent->elements.size();
		if (elemLen == 0) {
			this->offset = 0;
		} else {
			auto elem = *parent->elements.rbegin();
			int elemOffset = elem->offset;
			this->offset = offset;
			if (parent->prev() != nullptr) {
				if (parent->prev()->elements.size() == parent->elements.size() + 1) {
					if (parent->prev()->getTypeAt(elemOffset) == elem->type()) {
						this->offset = (*parent->prev()->elements.rbegin())->offset;
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
    int elemLen = parent->elements.size();
    if (elemLen > 1) {
        auto prevElem = parent->elements[elemLen - 2];
        if (prevElem->isBlockElement()) {
            auto prevBlock = dynamic_pointer_cast<ParseElementBlock>(prevElem);
            if (!prevBlock->isVirtual) {
                if (prevBlock->type() == ParseElementType::TYPE_LIST_ORDERED ||
                    prevBlock->type() == ParseElementType::TYPE_LIST_UNORDERED) {
                    if (parent->next() == nullptr) {
                        return this->text;
                    }
                    if (parent->next()->getTypeAt(prevElem->offset) != prevElem->type()) {
                        return this->text;
                    }
                    auto nextElem = parent->next()->getElementAt(prevElem->offset);
                    if (nextElem->isBlockElement()) {
                        auto nextBlock = dynamic_pointer_cast<ParseElementBlock>(nextElem);
                        if (!nextBlock->isVirtual) {
                            return this->text;
                        }
                    }
                    return "<p>" + this->text;
                }
            }
        }
    }
	if (parent->prev() == nullptr) {
		return "<p>" + this->text;
	}
	if (parent->prev()->getTypeAt(offset) != ParseElementType::TYPE_PARAGRAPH) {
		return "<p>" + this->text;
	}
    return this->text;
}

string ParseElementParagraph::generateCloseHtml() const {
	int elemLen = parent->elements.size();
	if (elemLen > 1) {
		auto prevElem = parent->elements[elemLen - 2];
		if (prevElem->isBlockElement()) {
			auto prevBlock = dynamic_pointer_cast<ParseElementBlock>(prevElem);
			if (!prevBlock->isVirtual) {
				if (prevBlock->type() == ParseElementType::TYPE_LIST_ORDERED ||
					prevBlock->type() == ParseElementType::TYPE_LIST_UNORDERED) {
					if (parent->next() == nullptr) {
						return "";
					}
					if (parent->next()->getTypeAt(prevElem->offset) != prevElem->type()) {
						return "";
					}
					auto nextElem = parent->next()->getElementAt(prevElem->offset);
					if (nextElem->isBlockElement()) {
						auto nextBlock = dynamic_pointer_cast<ParseElementBlock>(nextElem);
						if (!nextBlock->isVirtual) {
							return "";
						}
					}
				}
			}
		}
	}
    if (parent->next() == nullptr) {
        return "</p>";
    }
    if (parent->next()->getTypeAt(offset) != ParseElementType::TYPE_PARAGRAPH) {
        return "</p>";
    }
    elemLen = parent->next()->elements.size();
    if (elemLen > 1) {
		auto prevElem = parent->next()->elements[elemLen - 2];
        if (prevElem->isBlockElement()) {
            auto prevBlock = dynamic_pointer_cast<ParseElementBlock>(prevElem);
            if (!prevBlock->isVirtual) {
                if (prevBlock->type() == ParseElementType::TYPE_LIST_ORDERED ||
                    prevBlock->type() == ParseElementType::TYPE_LIST_UNORDERED) {
                    return "</p>";
                }
            }
        }
    }
    return "";
}
