#include "parse_line.h"
#include "parse_label_set.h"
#include "parse_elem_image_reference.h"
using namespace std;

ParseElementImageReference::ParseElementImageReference() : ParseElementImage() {
}

ParseElementType ParseElementImageReference::type() const {
    return ParseElementType::TYPE_IMAGE_REFERENCE;
}

int ParseElementImageReference::tryParse(const string& text, int offset) {
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

string ParseElementImageReference::generateOpenHtml() const {
    string link = this->parent->labelSet->getLink(this->_label);
    string title = this->parent->labelSet->getTitle(this->_label);
    if (link.length() == 0) {
        return this->translateAmp(this->text);
    }
    return this->generateOpenImageHtml(link, this->_alt, title);
}
