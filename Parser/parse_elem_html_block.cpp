#include "parse_line.h"
#include "parse_elem_html_block.h"
using namespace std;

ParseElementHtmlBlock::ParseElementHtmlBlock() : ParseElementBlock() {
}

ParseElementType ParseElementHtmlBlock::type() const {
    return ParseElementType::TYPE_HTML_BLOCK;
}

const string& ParseElementHtmlBlock::tag() const {
    return this->_tag;
}

void ParseElementHtmlBlock::setTag(const string& val) {
    this->_tag = "";
    for (auto ch : val) {
        if (ch >= 'A' && ch <= 'Z') {
            this->_tag += (char)(ch - 'A' + 'a');
        } else {
            this->_tag += ch;
        }
    }
}

bool ParseElementHtmlBlock::tryParse(const string &line, int offset, int& length) {
    int index = offset;
    this->isVirtual = false;
    if (parent->prev() != nullptr) {
        if (parent->prev()->getTypeAt(offset) == ParseElementType::TYPE_HTML_BLOCK) {
            auto elem = dynamic_pointer_cast<ParseElementHtmlBlock>(parent->prev()->getElementAt(offset));
            if (!elem->tag().empty()) {
                // Check whether it is the close tag.
                if (this->findCloseTagOffset(line, index)) {
                    if (this->matchToEnd(line, index)) {
                        if (this->tag() == elem->tag()) {
                            this->setTag("");
                            length = line.size() - offset;
                            return true;
                        }
                    }
                }
                // Inherit from last line.
                this->setTag(elem->tag());
                length = line.size() - offset;
                return true;
            }
        }
    }
    // Check whether it is the open tag.
    if (this->findOpenTagOffset(line, index)) {
        if (this->matchToEnd(line, index)) {
            length = line.size() - offset;
            return true;
        }
    }
    return false;
}

bool ParseElementHtmlBlock::inheritable() const {
	return true;
}

string ParseElementHtmlBlock::generateOpenHtml() const {
    return text;
}

bool ParseElementHtmlBlock::findOpenTagOffset(const string &line, int &index) {
    Status status = STATUS_BEGIN;
    int lineLength = line.length();
    while (index < lineLength) {
        char ch = line[index];
        switch (status) {
        case STATUS_BEGIN:
            if (ch == '<') {
                status = STATUS_LT;
            } else {
                return false;
            }
            break;
        case STATUS_LT:
            if (ch == ' ' || ch == '\t') {
                status = STATUS_LT;
            } else if (isalpha(ch)) {
                status = STATUS_TAG;
                return true;
            } else {
                return false;
            }
            break;
        default:
            return false;
        }
        ++index;
    }
    return false;
}

bool ParseElementHtmlBlock::findCloseTagOffset(const string &line, int &index) {
    Status status = STATUS_BEGIN;
    int lineLength = line.length();
    while (index < lineLength) {
        char ch = line[index];
        switch (status) {
        case STATUS_BEGIN:
            if (ch == '<') {
                status = STATUS_LT;
            } else {
                return false;
            }
            break;
        case STATUS_LT:
            if (ch == ' ' || ch == '\t') {
                status = STATUS_LT;
            } else if (ch == '/') {
                status = STATUS_SLASH;
            } else {
                return false;
            }
            break;
        case STATUS_SLASH:
            if (ch == ' ' || ch == '\t') {
                status = STATUS_SLASH;
            } else if (isalpha(ch)) {
                status = STATUS_TAG;
                return true;
            } else {
                return false;
            }
            break;
        default:
            return false;
        }
        ++index;
    }
    return false;
}

bool ParseElementHtmlBlock::matchToEnd(const string &line, int &index) {
    Status status = STATUS_TAG;
    int lineLength = line.length();
    int tagStart = index, tagEnd = index;
    bool first = true;
    while (index < lineLength) {
        char ch = line[index];
        switch (status) {
        case STATUS_TAG:
            if (isalpha(ch)) {
                status = STATUS_TAG;
            } else if (ch == ' ' || ch == '\t') {
                status = STATUS_SPACE_SUF;
                if (first) {
                    tagEnd = index;
                    first = false;
                }
            } else if (ch == '>') {
                status = STATUS_GT;
                if (first) {
                    tagEnd = index;
                    first = false;
                }
            } else {
                return false;
            }
            break;
        case STATUS_SPACE_SUF:
            if (ch == ' ' || ch == '\t') {
                status = STATUS_SPACE_SUF;
            } else if (ch == '>') {
                status = STATUS_GT;
            } else {
                return false;
            }
            break;
        case STATUS_GT:
            if (ch == ' ' || ch == '\t') {
                status = STATUS_GT;
            } else {
                return false;
            }
            break;
        default:
            return false;
        }
        ++index;
    }
    this->setTag(line.substr(tagStart, tagEnd - tagStart));
    return true;
}
