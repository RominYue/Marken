#include "ParseElementImageInline.h"

ParseElementImageInline::ParseElementImageInline() : ParseElementImage() {
}

ParseElementType ParseElementImageInline::type() const {
    return ParseElementType::TYPE_IMAGE_INLINE;
}

qint32 ParseElementImageInline::tryParse(const QString& text, qint32 offset) {
    if (text[offset] == '!') {
        qint32 length = text.length();
        qint32 index = offset + 1;
        if (this->ParserBrackets(text, index, this->_alt)) {
            if (this->ParserParentheses(text, index, this->_help)) {
                qint32 space = 0;
                length = this->_help.length();
                for (; space < length; ++space) {
                    if (this->_help[space] == ' ') {
                        break;
                    }
                }
                this->_link = this->getCleanedLink(this->_help.mid(0, space));
                if (space != length) {
                    this->_title = this->getCleanedTitle(this->_help.mid(space, this->_help.length() - space));
                } else {
                    this->_title = "";
                }
                return index - offset;
            }
        }
    }
    return 0;
}

QString ParseElementImageInline::generateOpenHtml() const {
    return this->generateOpenImageHtml(this->_link, this->_alt, this->_title);
}
