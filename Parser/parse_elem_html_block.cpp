#include "parse_line.h"
#include "parse_elem_html_block.h"
using namespace std;

static set<string> _acceptTags;

ParseElementHtmlBlock::ParseElementHtmlBlock() : ParseElementBlock() {
    if (_acceptTags.size() == 0) {
        _acceptTags.insert("address");
        _acceptTags.insert("blockquote");
        _acceptTags.insert("div");
        _acceptTags.insert("dl");
        _acceptTags.insert("fieldset");
        _acceptTags.insert("form");
        _acceptTags.insert("h1");
        _acceptTags.insert("h2");
        _acceptTags.insert("h3");
        _acceptTags.insert("h4");
        _acceptTags.insert("h5");
        _acceptTags.insert("h6");
        _acceptTags.insert("hr");
        _acceptTags.insert("noscript");
        _acceptTags.insert("ol");
        _acceptTags.insert("p");
        _acceptTags.insert("pre");
        _acceptTags.insert("table");
        _acceptTags.insert("ul");
        _acceptTags.insert("dd");
        _acceptTags.insert("dt");
        _acceptTags.insert("li");
        _acceptTags.insert("tbody");
        _acceptTags.insert("td");
        _acceptTags.insert("tfoot");
        _acceptTags.insert("th");
        _acceptTags.insert("thead");
        _acceptTags.insert("tr");
    }
}

ParseElementType ParseElementHtmlBlock::type() const {
    return ParseElementType::TYPE_HTML_BLOCK;
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
                    if (this->matchToGt(line, index)) {
                        if (this->matchToEnd(line, index)) {
                            if (this->tag() == elem->tag()) {
                                this->setTag("");
                                this->isVirtual = false;
                                length = line.size() - offset;
                                return true;
                            }
                        }
                    }
                }
                // Inherit from last line.
                if (elem->tag() != "") {
                    this->isVirtual = false;
                    this->setTag(elem->tag());
                    length = line.size() - offset;
                    return true;
                }
            }
        }
    }
    // Check whether it is the open tag.
    if (this->findOpenTagOffset(line, index)) {
        if (this->matchToGt(line, index)) {
            if (this->matchToEnd(line, index)) {
                if (_acceptTags.find(this->tag()) != _acceptTags.end()) {
                    length = line.size() - offset;
                    this->isVirtual = false;
                    return true;
                }
            }
        }
    }
    return false;
}

bool ParseElementHtmlBlock::inheritable() const {
    return true;
}

string ParseElementHtmlBlock::generateOpenHtml() const {
    if (this->isVirtual) {
        return "";
    }
    return text;
}
