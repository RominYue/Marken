#include "ParseLineData.h"
#include "ParseElementHeaderSetext.h"

ParseElementHeaderSetext::ParseElementHeaderSetext() : ParseElementHeader() {
}

ParseElementType ParseElementHeaderSetext::type() const {
    return ParseElementType::TYPE_HEADER_SETEXT;
}

bool ParseElementHeaderSetext::tryParse(const QString &line, int offset, int& length) {
    if (parent->prev() == nullptr) {
        return false;
    }
    int tempOffset = 0;
    if (parent->blocks.size() > 0) {
        tempOffset = parent->lastElement()->offset;
    }
    if (parent->prev()->getTypeAt(tempOffset) != ParseElementType::TYPE_PARAGRAPH) {
        return false;
    }
    if (parent->prev()->prev() != nullptr) {
        if (parent->prev()->prev()->getTypeAt(tempOffset) == ParseElementType::TYPE_PARAGRAPH) {
            return false;
        }
    }
    int lineLen = line.length();
    if (lineLen > offset) {
        QChar ch = line[offset];
        if (ch == '=' || ch == '-') {
            for (int i = offset + 1; i < lineLen; ++i) {
                if (line[i] != ch) {
                    for (; i < lineLen; ++i) {
                        if (!line[i].isSpace()) {
                            return false;
                        }
                    }
                }
            }
            if (ch == '=') {
                level = 1;
            } else {
                level = 2;
            }
            this->_isLower = true;
            int index = parent->prev()->getIndexAt(tempOffset);
            auto elem = parent->prev()->blocks[index];
            QSharedPointer<ParseElementHeaderSetext> setext(new ParseElementHeaderSetext());
            setext->parent = elem->parent;
            setext->offset = elem->offset;
            setext->offset = elem->offset;
            setext->length = elem->length;
            setext->text = elem->text;
            setext->level = level;
            setext->_isLower = false;
            parent->prev()->blocks[index] = qSharedPointerDynamicCast<ParseElementBlock>(setext);
            length = lineLen - offset;
            return true;
        }
    }
    return false;
}

QString ParseElementHeaderSetext::generateOpenHtml() const {
    if (this->_isLower) {
        return "";
    }
    return this->generateOpenTag();
}

QString ParseElementHeaderSetext::generateCloseHtml() const {
    if (this->_isLower) {
        return "";
    }
    return this->generateCloseTag();
}

bool ParseElementHeaderSetext::isLower() const {
    return this->_isLower;
}
