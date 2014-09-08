#include <algorithm>
#include "ParseLineData.h"
#include "ParseElementCodeFence.h"

ParseElementCodeFence::ParseElementCodeFence() :
    ParseElementBlock() {
}

ParseElementType ParseElementCodeFence::type() const {
    return ParseElementType::TYPE_CODE_FENCE;
}

bool ParseElementCodeFence::inheritable() const {
    return true;
}

bool ParseElementCodeFence::tryParse(const QString &line, qint32 offset, qint32& length) {
    qint32 lineLen = line.length();
    if (this->parent->prev() != nullptr) {
        if (this->parent->prev()->lastType() == ParseElementType::TYPE_CODE_FENCE) {
            auto prevFence = qSharedPointerDynamicCast<ParseElementCodeFence>(this->parent->prev()->lastElement());
            if (!prevFence->_isClose) {
                // Check whether it is the close fence.
                qint32 first = lineLen;
                for (qint32 i = offset; i < lineLen; ++i) {
                    if (line[i] == prevFence->_fenceChar) {
                        first = i;
                        break;
                    } else if (!line[i].isSpace()) {
                        break;
                    }
                }
                if (first != lineLen) {
                    qint32 num = 0;
                    for (qint32 i = first; i < lineLen; ++i) {
                        if (line[i] == prevFence->_fenceChar) {
                            ++num;
                        }
                    }
                    if (num >= prevFence->_fenceLen) {
                        bool clean = true;
                        for (qint32 i = first + num; i < lineLen; ++i) {
                            if (!line[i].isSpace()) {
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
                qint32 tempOffset = 0;
                qint32 prevBlockNum = this->parent->prev()->blocks.size();
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
        for (qint32 i = offset; i < lineLen; ++i) {
            if (line[i] == this->_fenceChar) {
                ++this->_fenceLen;
            }
        }
        if (this->_fenceLen < 3) {
            return false;
        }
        bool clean = true;
        for (qint32 i = offset + this->_fenceLen; i < lineLen; ++i) {
            if (line[i] == '`') {
                clean = false;
                break;
            }
        }
        if (clean) {
            this->_language = "";
            qint32 start = offset + this->_fenceLen;
            for (; start < lineLen; ++start) {
                if (!line[start].isSpace()) {
                    break;
                }
            }
            if (start != lineLen) {
                qint32 end = lineLen;
                for (qint32 i = start; i < lineLen; ++i) {
                    if (line[i].isSpace()) {
                        end = i;
                        break;
                    }
                }
                this->_language = line.mid(start, end - start);
            }
            this->_isClose = false;
            this->_fenceOffset = offset;
            length = lineLen - offset;
            return true;
        }
    }
    return false;
}

QString ParseElementCodeFence::generateOpenHtml() const {
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
    qint32 start = 0;
    qint32 len = std::min(this->_fenceOffset - this->offset, (qint32)this->text.length());
    for (qint32 i = 0; i < len; ++i) {
        if (text[i] == ' ') {
            ++start;
        } else if (text[i] == '\t') {
            ++start;
            len -= 3;
        }
    }
    return this->htmlEscaped(text.mid(start));
}

QString ParseElementCodeFence::generateCloseHtml() const {
    if (this->parent->next() == nullptr || this->_isClose) {
        return "</code></pre>";
    }
    return "";
}
