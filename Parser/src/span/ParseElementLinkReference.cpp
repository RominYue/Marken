#include "ParseLineData.h"
#include "ParseLabelSet.h"
#include "ParseElementLinkReference.h"

ParseElementLinkReference::ParseElementLinkReference() : ParseElementSpan(), ParseElementLink() {
}

ParseElementType ParseElementLinkReference::type() const {
    return ParseElementType::TYPE_LINK_REFERENCE;
}

qint32 ParseElementLinkReference::tryParse(const QString& text, qint32 offset) {
    qint32 index = offset;
    qint32 length = text.length();
    if (this->ParserBrackets(text, index, this->_inner)) {
        if (index < length) {
            if (text[index] == ' ') {
                ++index;
            }
        }
        if (this->ParserBrackets(text, index, this->_label)) {
            if (this->_label.length() == 0) {
                this->_label = this->getCleanedLabel(this->_inner);
            }
            this->parent->labelSet->addLinkElement(this->_label, this);
            return index - offset;
        }
    }
    return 0;
}

QString ParseElementLinkReference::generateOpenHtml() const {
    QString link = this->parent->labelSet->getLink(this->_label);
    QString title = this->parent->labelSet->getTitle(this->_label);
    if (link.length() == 0) {
        return this->htmlEscaped(this->text);
    }
    return this->generateOpenLinkHtml(link, title) + this->htmlEscaped(this->_inner);
}

QString ParseElementLinkReference::generateCloseHtml() const {
    QString link = this->parent->labelSet->getLink(this->_label);
    QString title = this->parent->labelSet->getTitle(this->_label);
    if (link.length() == 0) {
        return "";
    }
    return "</a>";
}

void ParseElementLinkReference::remove() {
    this->parent->labelSet->removeLinkElement(this->_label, this);
}
