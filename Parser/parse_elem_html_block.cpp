#include "parse_line.h"
#include "parse_elem_html_block.h"
using namespace std;

static set<string> _acceptTags;

ParseElementHtmlBlock::ParseElementHtmlBlock() : ParseElementBlock() {
    if (_acceptTags.size() == 0) {
        _acceptTags = {"article", "header", "aside", "hgroup", "blockquote",
                       "hr", "iframe", "body", "li", "map", "button", "object",
                       "canvas", "ol", "caption", "output", "col", "p",
                       "colgroup", "pre", "dd", "progress", "div", "section",
                       "dl", "table", "td", "dt", "tbody", "embed", "textarea",
                       "fieldset", "tfoot", "figcaption", "th", "figure",
                       "thead", "footer", "tr", "form", "ul", "h1", "h2", "h3",
                       "h4", "h5", "h6", "video", "script", "style"};
    }
}

ParseElementType ParseElementHtmlBlock::type() const {
    return ParseElementType::TYPE_HTML_BLOCK;
}

bool ParseElementHtmlBlock::tryParse(const string &line, int offset, int& length) {
    int lineLen = line.length();
    if (this->parent->prev() != nullptr) {
        if (this->parent->prev()->lastType() == ParseElementType::TYPE_HTML_BLOCK) {
            int tempOffset = 0;
            int prevBlockLen = this->parent->prev()->blocks.size();
            if (prevBlockLen > 1) {
                tempOffset = this->parent->prev()->blocks[prevBlockLen - 2]->offset;
            }
            if (offset >= tempOffset) {
                length = lineLen - offset;
                return true;
            }
        }
    }
    int first = offset;
    for (int i = offset; i < lineLen; ++i) {
        if (!isspace(line[i])) {
            first = i;
            break;
        }
    }
    if (first - offset >= 4) {
        return false;
    }
    int index = first;
    bool found = true;
    if (!this->findOpenTagOffset(line, index)) {
        index = first;
        if (!this->findCloseTagOffset(line, index)) {
            found = false;
        }
    }
    if (found) {
        this->matchToTagEnd(line, index);
        if (_acceptTags.find(this->tag()) != _acceptTags.end()) {
            length = lineLen - offset;
            return true;
        }
    }
    // HTML comment.
    if (lineLen - first >= 4) {
        if (line.substr(first, 4) == "<!--") {
            length = lineLen - offset;
            return true;
        }
    }
    // Processing instruction.
    // Declaration.
    if (lineLen - first >= 2) {
        if (line.substr(first, 2) == "<?" || line.substr(first, 2) == "<!") {
            length = lineLen - offset;
            return true;
        }
    }
    // CDATA section.
    if (lineLen - first >= 9) {
        if (line.substr(first, 9) == "<![CDATA[") {
            length = lineLen - offset;
            return true;
        }
    }
    return false;
}

string ParseElementHtmlBlock::generateOpenHtml() const {
    if (this->isVirtual) {
        return "";
    }
    return text;
}
