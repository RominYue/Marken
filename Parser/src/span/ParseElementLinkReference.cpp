#include "ParseLineData.h"
#include "ParseLabelSet.h"
#include "ParseElementLinkReference.h"

ParseElementLinkReference::ParseElementLinkReference() : ParseElementSpan(), ParseElementLink() {
}

ParseElementType ParseElementLinkReference::type() const {
    return ParseElementType::TYPE_LINK_REFERENCE;
}

QString ParseElementLinkReference::innerText() const {
    return this->_inner;
}

int ParseElementLinkReference::innerOffset() const {
    return 1;
}

int ParseElementLinkReference::tryParse(const QString& text, int offset) {
    int index = offset;
    int length = text.length();
    if (this->parseBrackets(text, index, this->_inner)) {
        int temp = index;
        if (index < length) {
            if (text[index] == ' ') {
                ++index;
            }
        }
        if (this->parseBrackets(text, index, this->_label)) {
            if (this->_label.length() == 0) {
                this->_label = this->_inner;
            }
            return index - offset;
        }
        this->_label = this->_inner;
        return temp - offset;
    }
    return 0;
}

QString ParseElementLinkReference::generateOpenHtml() const {
    QString link = this->parent->labelSet->getLink(this->_label);
    QString title = this->parent->labelSet->getTitle(this->_label);
    if (link.length() == 0) {
        return "[";
    }
    return this->generateOpenLinkHtml(link, title);
}

QString ParseElementLinkReference::generateCloseHtml() const {
    QString link = this->parent->labelSet->getLink(this->_label);
    QString title = this->parent->labelSet->getTitle(this->_label);
    if (link.length() == 0) {
        return text.mid(this->_inner.length() + 1, text.length() - this->_inner.length() - 1);
    }
    return "</a>";
}
