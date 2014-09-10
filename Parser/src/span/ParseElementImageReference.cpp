#include "ParseLineData.h"
#include "ParseLabelSet.h"
#include "ParseElementImageReference.h"

ParseElementImageReference::ParseElementImageReference() : ParseElementImage() {
}

ParseElementType ParseElementImageReference::type() const {
    return ParseElementType::TYPE_IMAGE_REFERENCE;
}

int ParseElementImageReference::tryParse(const QString& text, int offset) {
    if (text[offset] == '!') {
        int length = text.length();
        int index = offset + 1;
        if (this->parseBrackets(text, index, this->_alt)) {
            if (index < length) {
                if (text[index] == ' ') {
                    ++index;
                }
            }
            if (this->parseBrackets(text, index, this->_label)) {
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
