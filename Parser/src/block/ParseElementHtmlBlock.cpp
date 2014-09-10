#include "ParseLineData.h"
#include "ParseElementHtmlBlock.h"

static set<QString> _acceptTags;

ParseElementHtmlBlock::ParseElementHtmlBlock() : ParseElementBlock() {
    if (_acceptTags.size() == 0) {
        _acceptTags.insert("article");
        _acceptTags.insert("header");
        _acceptTags.insert("aside");
        _acceptTags.insert("hgroup");
        _acceptTags.insert("blockquote");
        _acceptTags.insert("hr");
        _acceptTags.insert("iframe");
        _acceptTags.insert("body");
        _acceptTags.insert("li");
        _acceptTags.insert("QMap");
        _acceptTags.insert("button");
        _acceptTags.insert("object");
        _acceptTags.insert("canvas");
        _acceptTags.insert("ol");
        _acceptTags.insert("caption");
        _acceptTags.insert("output");
        _acceptTags.insert("col");
        _acceptTags.insert("p");
        _acceptTags.insert("colgroup");
        _acceptTags.insert("pre");
        _acceptTags.insert("dd");
        _acceptTags.insert("progress");
        _acceptTags.insert("div");
        _acceptTags.insert("section");
        _acceptTags.insert("dl");
        _acceptTags.insert("table");
        _acceptTags.insert("td");
        _acceptTags.insert("dt");
        _acceptTags.insert("tbody");
        _acceptTags.insert("embed");
        _acceptTags.insert("textarea");
        _acceptTags.insert("fieldset");
        _acceptTags.insert("tfoot");
        _acceptTags.insert("figcaption");
        _acceptTags.insert("th");
        _acceptTags.insert("figure");
        _acceptTags.insert("thead");
        _acceptTags.insert("footer");
        _acceptTags.insert("tr");
        _acceptTags.insert("form");
        _acceptTags.insert("ul");
        _acceptTags.insert("h1");
        _acceptTags.insert("h2");
        _acceptTags.insert("h3");
        _acceptTags.insert("h4");
        _acceptTags.insert("h5");
        _acceptTags.insert("h6");
        _acceptTags.insert("video");
        _acceptTags.insert("script");
        _acceptTags.insert("style");
    }
}

ParseElementType ParseElementHtmlBlock::type() const {
    return ParseElementType::TYPE_HTML_BLOCK;
}

bool ParseElementHtmlBlock::tryParse(const QString &line, int offset, int& length) {
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
        if (!line[i].isSpace()) {
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
        if (line.mid(first, 4) == "<!--") {
            length = lineLen - offset;
            return true;
        }
    }
    // Processing instruction.
    // Declaration.
    if (lineLen - first >= 2) {
        if (line.mid(first, 2) == "<?" || line.mid(first, 2) == "<!") {
            length = lineLen - offset;
            return true;
        }
    }
    // CDATA section.
    if (lineLen - first >= 9) {
        if (line.mid(first, 9) == "<![CDATA[") {
            length = lineLen - offset;
            return true;
        }
    }
    return false;
}

QString ParseElementHtmlBlock::generateOpenHtml() const {
    if (this->isVirtual) {
        return "";
    }
    return text;
}
