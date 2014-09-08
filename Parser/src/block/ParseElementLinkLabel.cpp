#include "ParseLineData.h"
#include "ParseLabelSet.h"
#include "ParseElementLinkLabel.h"

ParseElementLinkLabel::ParseElementLinkLabel() : ParseElementBlock(), ParseElementLink() {
}

ParseElementType ParseElementLinkLabel::type() const {
    return ParseElementType::TYPE_LINK_LABEL;
}

bool ParseElementLinkLabel::tryParse(const QString &line, qint32 offset, qint32& length) {
    qint32 lineLen = line.length();
    qint32 index = offset;
    if (this->ParserBrackets(line, index, this->label)) {
        this->label = this->getCleanedLabel(this->label);
        if (index < lineLen) {
            if (line[index] == ':') {
                for (++index; index < lineLen; ++index) {
                    if (!line[index].isSpace()) {
                        break;
                    }
                }
                if (index < lineLen) {
                    qint32 start = index;
                    for (++index; index < lineLen; ++index) {
                        if (line[index].isSpace()) {
                            break;
                        }
                    }
                    this->link = this->getCleanedLink(line.mid(start, index - start));
                    for (++index; index < lineLen; ++index) {
                        if (!line[index].isSpace()) {
                            break;
                        }
                    }
                    if (index < lineLen) {
                        this->title = this->getCleanedTitle(line.mid(index, lineLen - index));
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
        auto elem = this->parent->prev()->lastElement();
        if (offset <= elem->offset) {
            return false;
        }
        if (elem->type() == ParseElementType::TYPE_LINK_LABEL) {
            if (!text[offset].isSpace()) {
                auto linkLabel = qSharedPointerDynamicCast<ParseElementLinkLabel>(elem);
                length = lineLen - offset;
                this->label = linkLabel->label;
                this->title = this->getCleanedTitle(line.mid(offset, lineLen - offset));
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
