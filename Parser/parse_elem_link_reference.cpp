#include "parse_line.h"
#include "parse_label_set.h"
#include "parse_elem_link_reference.h"
using namespace std;

ParseElementLinkReference::ParseElementLinkReference() : ParseElementSpan(), ParseElementLink() {
}

ParseElementType ParseElementLinkReference::type() const {
    return ParseElementType::TYPE_LINK_REFERENCE;
}

int ParseElementLinkReference::tryParse(const string& text, int offset) {
    int index = offset;
    int length = text.length();
    if (this->parseBrackets(text, index, this->_inner)) {
        if (index < length) {
            if (text[index] == ' ') {
                ++index;
            }
        }
        if (this->parseBrackets(text, index, this->_label)) {
            if (this->_label.length() == 0) {
                this->_label = this->getCleanedLabel(this->_inner);
            }
            this->parent->labelSet->addLinkElement(this->_label, this);
            return index - offset;
        }
    }
    return 0;
}

string ParseElementLinkReference::generateOpenHtml() const {
    string link = this->parent->labelSet->getLink(this->_label);
    string title = this->parent->labelSet->getTitle(this->_label);
    if (link.length() == 0) {
        return this->translateAmp(this->text);
    }
    return this->generateOpenLinkHtml(link, title) + this->translateAmp(this->_inner);
}

string ParseElementLinkReference::generateCloseHtml() const {
    string link = this->parent->labelSet->getLink(this->_label);
    string title = this->parent->labelSet->getTitle(this->_label);
    if (link.length() == 0) {
        return "";
    }
    return "</a>";
}

void ParseElementLinkReference::remove() {
    this->parent->labelSet->removeLinkElement(this->_label, this);
}
