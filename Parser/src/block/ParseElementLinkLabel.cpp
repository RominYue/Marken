#include "ParseLineData.h"
#include "ParseLabelSet.h"
#include "ParseElementLinkLabel.h"

ParseElementLinkLabel::ParseElementLinkLabel() : ParseElementBlock(), ParseElementLink() {
}

ParseElementType ParseElementLinkLabel::type() const {
    return ParseElementType::TYPE_LINK_LABEL;
}

bool ParseElementLinkLabel::tryParse(const QString &line, int offset, int& length) {
    if (parent->prev() != nullptr) {
        if (parent->prev()->lastType() == ParseElementType::TYPE_PARAGRAPH) {
            return false;
        }
    }
    int index = offset;
    int lineLen = line.length();
    if (this->parseBrackets(line, index, this->label)) {
        if (index < lineLen) {
            if (line[index] == ':') {
                ++index;
                if (this->parseLink(line, index, this->link)) {
                    if (this->parseTitle(line, index, this->title)) {
                        length = lineLen - offset;
                        this->isBegin = true;
                        return true;
                    }
                }
            }
        }
    }
    if (parent->prev() != nullptr) {
        if (parent->prev()->lastType() == ParseElementType::TYPE_LINK_LABEL) {
            if (this->link == "") {
                auto prevLabel = qSharedPointerDynamicCast<ParseElementLinkLabel>(parent->prev()->lastElement());
                this->label = prevLabel->label;
                if (this->parseLink(line, index, this->link)) {
                    if (this->link.length() > 0) {
                        if (this->parseTitle(line, index, this->title)) {
                            length = lineLen - offset;
                            this->isBegin = false;
                            return true;
                        }
                    }
                }
            } else if (this->title == "") {
                auto prevLabel = qSharedPointerDynamicCast<ParseElementLinkLabel>(parent->prev()->lastElement());
                this->label = prevLabel->label;
                this->link = prevLabel->link;
                if (this->parseTitle(line, index, this->title)) {
                    if (this->title.length() > 0) {
                        length = lineLen - offset;
                        this->isBegin = false;
                        return true;
                    }
                }
            }
        }
    }
    return false;
}

QString ParseElementLinkLabel::generateOpenHtml() const {
    QString link = this->parent->labelSet->getLink(this->label);
    if (link.length() == 0) {
        return "<p>" + this->htmlEscaped(this->text) + "</p>";
    }
    return "";
}