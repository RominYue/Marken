#include "parse_line.h"
#include "parse_elem_html_block.h"
using namespace std;

ParseElementHtmlBlock::ParseElementHtmlBlock() : ParseElementBlock() {
}

ParseElementType ParseElementHtmlBlock::type() const {
    return ParseElementType::TYPE_HTML_BLOCK;
}

bool ParseElementHtmlBlock::tryParse(const string &line, int offset, int& length) {
    int index = offset;
    this->isVirtual = false;
    if (parent->prev() != nullptr) {
        if (parent->prev()->getTypeAt(offset) == ParseElementType::TYPE_HTML_BLOCK) {
            auto elem = dynamic_pointer_cast<ParseElementHtmlBlock>(parent->prev()->getElementAt(offset));
            if (!elem->tag().empty()) {
                // Check whether it is the close tag.
                if (this->findCloseTagOffset(line, index)) {
                    if (this->matchToGt(line, index)) {
                        if (this->matchToEnd(line, index)) {
                            if (this->tag() == elem->tag()) {
                                this->setTag("");
                                length = line.size() - offset;
                                return true;
                            }
                        }
                    }
                }
                // Inherit from last line.
                this->setTag(elem->tag());
                length = line.size() - offset;
                return true;
            }
        }
    }
    // Check whether it is the open tag.
    if (this->findOpenTagOffset(line, index)) {
        if (this->matchToGt(line, index)) {
            if (this->matchToEnd(line, index)) {
                length = line.size() - offset;
                return true;
            }
        }
    }
    return false;
}

bool ParseElementHtmlBlock::inheritable() const {
    return true;
}

string ParseElementHtmlBlock::generateOpenHtml() const {
    return text;
}
