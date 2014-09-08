#include "ParseLineData.h"
#include "ParseLabelSet.h"
#include "ParseElementImageReference.h"

ParseElementImageReference::ParseElementImageReference() : ParseElementImage() {
}

ParseElementType ParseElementImageReference::type() const {
    return ParseElementType::TYPE_IMAGE_REFERENCE;
}

qint32 ParseElementImageReference::tryParse(const QString& text, qint32 offset) {
    if (text[offset] == '!') {
        qint32 length = text.length();
        qint32 index = offset + 1;
        if (this->ParserBrackets(text, index, this->_alt)) {
            if (index < length) {
                if (text[index] == ' ') {
                    ++index;
                }
            }
            if (this->ParserBrackets(text, index, this->_label)) {
                if (this->_label.length() == 0) {
                    this->_label = this->getCleanedLabel(this->_alt);
                }
                this->parent->labelSet->addLinkElement(this->_label, this);
                return index - offset;
            }
        }
    }
    return 0;
}

QString ParseElementImageReference::generateOpenHtml() const {
    QString link = this->parent->labelSet->getLink(this->_label);
    QString title = this->parent->labelSet->getTitle(this->_label);
    if (link.length() == 0) {
        return this->htmlEscaped(this->text);
    }
    return this->generateOpenImageHtml(link, this->_alt, title);
}
