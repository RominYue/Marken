#include "parse_line.h"
#include "parse_elem_code_block.h"
using namespace std;

ParseElementCodeBlock::ParseElementCodeBlock() : ParseElementBlock() {
}

ParseElementType ParseElementCodeBlock::type() const {
    return ParseElementType::TYPE_CODE_BLOCK;
}

bool ParseElementCodeBlock::tryParse(const string &line, int offset, int& length) {
    int lastOffset = 0;
    if (parent->prev() != nullptr) {
        if (parent->prev()->blocks.size() > 0) {
            lastOffset = (*parent->prev()->blocks.rbegin())->offset;
        }
    }
    if (offset == lastOffset) {
        int lineLen = line.length();
        int spaceCnt = 0;
        int tabCnt = 0;
        for (int index = offset; index < lineLen; ++index) {
            if (line[index] == '\t') {
                tabCnt += 1;
                spaceCnt -= lineLen;
            } else if (line[index] == ' ') {
                spaceCnt += 1;
                tabCnt -= lineLen;
            } else {
                return false;
            }
            if (tabCnt == 1 || spaceCnt == 4) {
                length = lineLen - offset;
                return true;
            }
        }
    }
    return false;
}

string ParseElementCodeBlock::generateOpenHtml() const {
    string html;
    if (parent->prev() == nullptr) {
        html += "<pre><code>";
    } else if (parent->prev()->getTypeAt(offset) != ParseElementType::TYPE_CODE_BLOCK) {
        html += "<pre><code>";
    }
    int index = 1;
    if (this->text.size() > 0) {
        if (this->text[0] == ' ') {
            index = 4;
        }
    }
    int len = text.length();
    html += this->translateAmp(text.substr(index, len - index));
    return html;
}

string ParseElementCodeBlock::generateCloseHtml() const {
    if (parent->next() == nullptr) {
        return "</code></pre>";
    } else if (parent->next()->getTypeAt(offset) != ParseElementType::TYPE_CODE_BLOCK) {
        return "</code></pre>";
    }
    return "";
}
