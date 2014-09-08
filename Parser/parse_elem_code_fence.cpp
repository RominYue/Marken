#include <algorithm>
#include "parse_line.h"
#include "parse_elem_code_fence.h"
using namespace std;

ParseElementCodeFence::ParseElementCodeFence() :
    ParseElementBlock() {
}

ParseElementType ParseElementCodeFence::type() const {
    return ParseElementType::TYPE_CODE_FENCE;
}

bool ParseElementCodeFence::inheritable() const {
    return true;
}

bool ParseElementCodeFence::tryParse(const string &line, int offset, int& length) {
    int lineLen = line.length();
    if (this->parent->prev() != nullptr) {
        if (this->parent->prev()->lastType() == ParseElementType::TYPE_CODE_FENCE) {
            auto prevFence = dynamic_pointer_cast<ParseElementCodeFence>(this->parent->prev()->lastElement());
            if (!prevFence->_isClose) {
                // Check whether it is the close fence.
                int first = lineLen;
                for (int i = offset; i < lineLen; ++i) {
                    if (line[i] == prevFence->_fenceChar) {
                        first = i;
                        break;
                    } else if (line[i] != ' ' && line[i] != '\t') {
                        break;
                    }
                }
                if (first != lineLen) {
                    int num = 0;
                    for (int i = first; i < lineLen; ++i) {
                        if (line[i] == prevFence->_fenceChar) {
                            ++num;
                        }
                    }
                    if (num >= prevFence->_fenceLen) {
                        bool clean = true;
                        for (int i = first + num; i < lineLen; ++i) {
                            if (line[i] != ' ' && line[i] != '\t') {
                                clean = false;
                                break;
                            }
                        }
                        if (clean) {
                            this->_isClose = true;
                            this->_fenceChar = 0;
                            length = lineLen - offset;
                            return true;
                        }
                    }
                }
                // Inherit from previous line.
                int tempOffset = 0;
                int prevBlockNum = this->parent->prev()->blocks.size();
                if (prevBlockNum > 1) {
                    tempOffset = this->parent->prev()->blocks[prevBlockNum - 2]->offset + 1;
                }
                if (offset >= tempOffset) {
                    this->_isClose = false;
                    this->_fenceChar = prevFence->_fenceChar;
                    this->_fenceLen = prevFence->_fenceLen;
                    this->_fenceOffset = prevFence->_fenceOffset;
                    length = lineLen - offset;
                    return true;
                }
                return false;
            }
        }
    }
    // Check whether it is the open fence.
    if (line[offset] == '`' || line[offset] == '~') {
        this->_fenceChar = line[offset];
        this->_fenceLen = 0;
        for (int i = offset; i < lineLen; ++i) {
            if (line[i] == this->_fenceChar) {
                ++this->_fenceLen;
            }
        }
        if (this->_fenceLen < 3) {
            return false;
        }
        bool clean = true;
        for (int i = offset + this->_fenceLen; i < lineLen; ++i) {
            if (line[i] == '`') {
                clean = false;
                break;
            }
        }
        if (clean) {
            this->_language = "";
            int start = offset + this->_fenceLen;
            for (; start < lineLen; ++start) {
                if (line[start] != ' ' && line[start] != '\t') {
                    break;
                }
            }
            if (start != lineLen) {
                int end = lineLen;
                for (int i = start; i < lineLen; ++i) {
                    if (line[i] == ' ' || line[i] == '\t') {
                        end = i;
                        break;
                    }
                }
                this->_language = line.substr(start, end - start);
            }
            this->_isClose = false;
            this->_fenceOffset = offset;
            length = lineLen - offset;
            return true;
        }
    }
    return false;
}

string ParseElementCodeFence::generateOpenHtml() const {
    if (this->isVirtual) {
        return "";
    }
    if (this->parent->prev() == nullptr || this->parent->prev()->lastType() != ParseElementType::TYPE_CODE_FENCE) {
        if (this->_language.length() == 0) {
            return "<pre><code>";
        }
        return "<pre><code class=\"language-" + this->_language + "\">";
    }
    if (this->_isClose) {
        return "";
    }
    int start = 0;
    int len = min(this->_fenceOffset - this->offset, (int)this->text.length());
    for (int i = 0; i < len; ++i) {
        if (text[i] == ' ') {
            ++start;
        } else if (text[i] == '\t') {
            ++start;
            len -= 3;
        }
    }
    return this->translateAmp(text.substr(start));
}

string ParseElementCodeFence::generateCloseHtml() const {
    if (this->parent->next() == nullptr || this->_isClose) {
        return "</code></pre>";
    }
    return "";
}
