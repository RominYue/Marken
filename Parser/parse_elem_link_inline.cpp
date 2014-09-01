#include "parse_elem_link_inline.h"
using namespace std;

ParseElementLinkInline::ParseElementLinkInline() : ParseElementLink() {
}

ParseElementType ParseElementLinkInline::type() const {
    return ParseElementType::TYPE_LINK_INLINE;
}

int ParseElementLinkInline::tryParse(const string& text, int offset) {
    int index = offset;
    int length = text.length();
    if (this->parseBrackets(text, index, this->_inner)) {
        if (this->parseParentheses(text, index, this->_help)) {
            int space = 0;
            length = this->_help.length();
            for (; space < length; ++space) {
                if (this->_help[space] == ' ') {
                    break;
                }
            }
            this->_link = this->_help.substr(0, space);
            if (space != length) {
                this->_title = this->getCleanedTitle(this->_help.substr(space, this->_help.length() - space));
            } else {
                this->_title = "";
            }
            return index - offset;
        }
    }
    return 0;
}

string ParseElementLinkInline::generateOpenHtml() const {
    if (this->_title.length() > 0) {
        return string("<a href=\"") + this->_link + string("\" title=\"") + this->_title + string("\">");
    }
    return string("<a href=\"") + this->_link + string("\">");
}

string ParseElementLinkInline::generateCloseHtml() const {
    return "</a>";
}

string ParseElementLinkInline::innerText() const {
    return this->_inner;
}

int ParseElementLinkInline::innerOffset() const {
    return 1;
}
