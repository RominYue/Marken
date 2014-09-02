#include <cstdio>
#include "parse_elem_link_automatic.h"
using namespace std;

ParseElementLinkAutomatic::ParseElementLinkAutomatic() : ParseElementSpan(), ParseElementLink() {
}

ParseElementType ParseElementLinkAutomatic::type() const {
    return ParseElementType::TYPE_LINK_AUTOMATIC;
}

int ParseElementLinkAutomatic::tryParse(const string& text, int offset) {
    int index = offset;
    if (this->parseOpenClose(text, index, this->_link, '<', '>')) {
        if (isLink() || isEmail()) {
            return index - offset;
        }
    }
    return 0;
}

string ParseElementLinkAutomatic::generateOpenHtml() const {
    if (this->isLink()) {
        return this->generateOpenLinkHtml(this->_link, "") + this->_link + "</a>";
    }
    return this->generateOpenLinkHtml(this->translateToAmp("mailto:" + this->_link), "") +
           this->translateToAmp(this->_link) + "</a>";
}

bool ParseElementLinkAutomatic::isLink() const {
    if (this->_link.size() >= 7) {
        return this->_link.substr(0, 7) == "http://";
    }
    return false;
}

bool ParseElementLinkAutomatic::isEmail() const {
    enum EmailStatus {
        STATUS_TEXT1,
        STATUS_AT,
        STATUS_TEXT2,
        STATUS_DOT,
        STATUS_TEXT3,
    };
    EmailStatus status = STATUS_TEXT1;
    int length = this->_link.length();
    for (int i = 0; i < length; ++i) {
        char ch = this->_link[i];
        switch (status) {
        case STATUS_TEXT1:
            if (ch == '@') {
                status = STATUS_AT;
            } else if (ch == ' ' || ch == '\t') {
                return false;
            } else if (ch < 0) {
                return false;
            }
            break;
        case STATUS_AT:
            if (ch == ' ' || ch == '\t') {
                return false;
            } else if (ch > 0) {
                status = STATUS_TEXT2;
            } else {
                return false;
            }
            break;
        case STATUS_TEXT2:
            if (ch == '.') {
                status = STATUS_DOT;
            } else if (ch == ' ' || ch == '\t') {
                return false;
            } else if (ch < 0) {
                return false;
            }
            break;
        case STATUS_DOT:
            if (ch == ' ' || ch == '\t') {
                return false;
            } else if (ch > 0) {
                status = STATUS_TEXT3;
            } else {
                return false;
            }
            break;
        case STATUS_TEXT3:
            if (ch == ' ' || ch == '\t') {
                return false;
            } else if (ch < 0) {
                return false;
            }
            break;
        default:
            break;
        }
    }
    return status == STATUS_TEXT3;
}

string ParseElementLinkAutomatic::translateToAmp(const string& text) const {
    string amp;
    char buffer[16];
    int length = text.length();
    for (int i = 0; i < length; ++i) {
        sprintf(buffer, "%d", text[i]);
        amp += string("&#") + buffer + ";";
    }
    return amp;
}
