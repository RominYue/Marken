#include "ParseElementLinkInline.h"

ParseElementLinkInline::ParseElementLinkInline() : ParseElementSpan(), ParseElementLink() {
}

ParseElementType ParseElementLinkInline::type() const {
    return ParseElementType::TYPE_LINK_INLINE;
}

qint32 ParseElementLinkInline::tryParse(const QString& text, qint32 offset) {
    qint32 index = offset;
    qint32 length = text.length();
    if (this->ParserBrackets(text, index, this->_inner)) {
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
    return 0;
}

QString ParseElementLinkInline::generateOpenHtml() const {
    return this->generateOpenLinkHtml(this->_link, this->_title);
}

QString ParseElementLinkInline::generateCloseHtml() const {
    return "</a>";
}

QString ParseElementLinkInline::innerText() const {
    return this->_inner;
}

qint32 ParseElementLinkInline::innerOffset() const {
    return 1;
}
