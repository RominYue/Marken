#include "parse_elem_image_inline.h"
using namespace std;

ParseElementImageInline::ParseElementImageInline() : ParseElementImage() {
}

ParseElementType ParseElementImageInline::type() const {
    return ParseElementType::TYPE_IMAGE_INLINE;
}

int ParseElementImageInline::tryParse(const string& text, int offset) {
    if (text[offset] == '!') {
        int length = text.length();
        int index = offset + 1;
        if (this->parseBrackets(text, index, this->_alt)) {
            if (this->parseParentheses(text, index, this->_help)) {
                int space = 0;
                length = this->_help.length();
                for (; space < length; ++space) {
                    if (this->_help[space] == ' ') {
                        break;
                    }
                }
                this->_link = this->getCleanedLink(this->_help.substr(0, space));
                if (space != length) {
                    this->_title = this->getCleanedTitle(this->_help.substr(space, this->_help.length() - space));
                } else {
                    this->_title = "";
                }
                return index - offset;
            }
        }
    }
    return 0;
}

string ParseElementImageInline::generateOpenHtml() const {
    return this->generateOpenImageHtml(this->_link, this->_alt, this->_title);
}
