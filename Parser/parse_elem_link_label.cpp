#include "parse_line.h"
#include "parse_label_set.h"
#include "parse_elem_link_label.h"
using namespace std;

ParseElementLinkLabel::ParseElementLinkLabel() : ParseElementBlock(), ParseElementLink() {
}

ParseElementType ParseElementLinkLabel::type() const {
    return ParseElementType::TYPE_LINK_LABEL;
}

bool ParseElementLinkLabel::tryParse(const string &line, int offset, int& length) {
    int lineLen = line.length();
    int index = offset;
    if (this->parseBrackets(line, index, this->label)) {
        this->label = this->getCleanedLabel(this->label);
        if (index < lineLen) {
            if (line[index] == ':') {
                for (++index; index < lineLen; ++index) {
                    if (!isspace(line[index])) {
                        break;
                    }
                }
                if (index < lineLen) {
                    int start = index;
                    for (++index; index < lineLen; ++index) {
                        if (isspace(line[index])) {
                            break;
                        }
                    }
                    this->link = this->getCleanedLink(line.substr(start, index - start));
                    for (++index; index < lineLen; ++index) {
                        if (!isspace(line[index])) {
                            break;
                        }
                    }
                    if (index < lineLen) {
                        this->title = this->getCleanedTitle(line.substr(index, lineLen - index));
                    } else {
                        this->title = "";
                    }
                    length = lineLen - offset;
                    this->isBegin = true;
                    this->addToLabelSet();
                    return true;
                }
            }
        }
    } else {
        if (this->parent->prev() == nullptr) {
            return false;
        }
        if (this->parent->prev()->blocks.size() == 0) {
            return false;
        }
        auto elem = *this->parent->prev()->blocks.rbegin();
        if (offset <= elem->offset) {
            return false;
        }
        if (elem->type() == ParseElementType::TYPE_LINK_LABEL) {
            if (!isspace(text[offset])) {
                auto linkLabel = dynamic_pointer_cast<ParseElementLinkLabel>(elem);
                length = lineLen - offset;
                this->label = linkLabel->label;
                this->title = this->getCleanedTitle(line.substr(offset, lineLen - offset));
                this->isBegin = false;
                this->addToLabelSet();
                return true;
            }
        }
    }
    return false;
}

void ParseElementLinkLabel::remove() {
    if (this->isBegin) {
        this->parent->labelSet->removeLinkLabel(this);
    } else {
        this->parent->labelSet->removeLinkTitle(this);
    }
}

void ParseElementLinkLabel::addToLabelSet() {
    if (this->isBegin) {
        this->parent->labelSet->addLinkLabel(this);
    } else {
        this->parent->labelSet->addLinkTitle(this);
    }
}
