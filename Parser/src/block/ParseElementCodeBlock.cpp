#include "ParseLineData.h"
#include "ParseElementCodeBlock.h"

ParseElementCodeBlock::ParseElementCodeBlock() : ParseElementBlock() {
}

ParseElementType ParseElementCodeBlock::type() const {
    return ParseElementType::TYPE_CODE_BLOCK;
}

bool ParseElementCodeBlock::inheritable() const {
    return true;
}

bool ParseElementCodeBlock::tryParse(const QString &line, int offset, int& length) {
    int lastOffset = 0;
    if (parent->prev() != nullptr) {
        if (parent->prev()->lastType() == ParseElementType::TYPE_PARAGRAPH) {
            return false;
        }
        if (parent->prev()->blocks.size() > 0) {
            lastOffset = parent->prev()->lastElement()->offset;
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
                this->_isEmpty = true;
                for (++index; index < lineLen; ++index) {
                    if (!line[index].isSpace()) {
                        this->_isEmpty = false;
                        break;
                    }
                }
                length = lineLen - offset;
                return true;
            }
        }
    }
    return false;
}

QString ParseElementCodeBlock::generateOpenHtml() const {
    if (this->isVirtual) {
        return "";
    }
    QString html;
    bool isPrevEmpty = true;
    auto line = parent->prev();
    while (line != nullptr) {
        if (line->lastType() == ParseElementType::TYPE_CODE_BLOCK) {
            auto elem = qSharedPointerDynamicCast<ParseElementCodeBlock>(line->lastElement());
            if (!elem->isVirtual && !elem->_isEmpty) {
                isPrevEmpty = false;
                break;
            }
        } else {
            break;
        }
        line = line->prev();
    }
    if (this->_isEmpty) {
        if (isPrevEmpty) {
            return "";
        }
    } else {
        if (isPrevEmpty) {
            html += "<pre><code>";
        }
    }
    int index = 1;
    if (this->text.size() > 0) {
        if (this->text[0] == ' ') {
            index = 4;
        }
    }
    int len = text.length();
    html += this->htmlEscaped(text.mid(index, len - index));
    return html;
}

QString ParseElementCodeBlock::generateCloseHtml() const {
    if (this->isVirtual) {
        return "";
    }
    bool isNextEmpty = true;
    auto line = parent->next();
    while (line != nullptr) {
        if (line->lastType() == ParseElementType::TYPE_CODE_BLOCK) {
            auto elem = qSharedPointerDynamicCast<ParseElementCodeBlock>(line->lastElement());
            if (!elem->isVirtual && !elem->_isEmpty) {
                isNextEmpty = false;
                break;
            }
        } else {
            break;
        }
        line = line->next();
    }
    if (this->_isEmpty) {
        if (isNextEmpty) {
            return "";
        }
    } else {
        if (isNextEmpty) {
            return "</code></pre>";
        }
    }
    return "";
}
