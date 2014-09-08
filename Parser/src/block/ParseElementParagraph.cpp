#include "ParseLineData.h"
#include "ParseElementListOrdered.h"
#include "ParseElementListUnordered.h"
#include "ParseElementQuote.h"
#include "ParseElementParagraph.h"

ParseElementParagraph::ParseElementParagraph() : ParseElementBlock() {
}

ParseElementType ParseElementParagraph::type() const {
    return ParseElementType::TYPE_PARAGRAPH;
}

bool ParseElementParagraph::stopParsing(qint32 offset) const {
    Q_UNUSED(offset);
    return false;
}

bool ParseElementParagraph::tryParse(const QString &line, qint32 offset, qint32& length) {
    this->isVirtual = false;
    if (!line[offset].isSpace()) {
        if (parent->prev() != nullptr) {
            if (parent->prev()->blocks.size() > 0) {
                auto lastElem = parent->prev()->lastElement();
                if (lastElem->type() == ParseElementType::TYPE_EMPTY) {
                } else if (parent->prev()->getTypeAt(offset) == ParseElementType::TYPE_LIST_ORDERED) {
                    QSharedPointer<ParseElementListOrdered> elem(new ParseElementListOrdered());
                    elem->isVirtual = true;
                    elem->offset = offset;
                    elem->offset = 0;
                    elem->length = 0;
                    elem->parent = this->parent;
                    this->parent->blocks.push_back(qSharedPointerDynamicCast<ParseElementBlock>(elem));
                } else if (parent->prev()->getTypeAt(offset) == ParseElementType::TYPE_LIST_UNORDERED) {
                    QSharedPointer<ParseElementListUnordered> elem(new ParseElementListUnordered());
                    elem->isVirtual = true;
                    elem->offset = offset;
                    elem->offset = 0;
                    elem->length = 0;
                    elem->parent = this->parent;
                    this->parent->blocks.push_back(qSharedPointerDynamicCast<ParseElementBlock>(elem));
                } else if (parent->prev()->getTypeAt(offset) == ParseElementType::TYPE_QUOTE) {
                    QSharedPointer<ParseElementQuote> elem(new ParseElementQuote());
                    elem->isVirtual = true;
                    elem->offset = offset;
                    elem->offset = 0;
                    elem->length = 0;
                    elem->parent = parent;
                    elem->parent = this->parent;
                    this->parent->blocks.push_back(qSharedPointerDynamicCast<ParseElementBlock>(elem));
                }
            }
        }
        qint32 elemLen = parent->blocks.size();
        if (elemLen == 0) {
            this->offset = 0;
        } else {
            auto elem = parent->lastElement();
            qint32 elemOffset = elem->offset;
            this->offset = offset;
            if (parent->prev() != nullptr) {
                if (parent->prev()->blocks.size() == parent->blocks.size() + 1) {
                    if (parent->prev()->getTypeAt(elemOffset) == elem->type()) {
                        auto prevElem = parent->prev()->lastElement();
                        if (prevElem->type() == ParseElementType::TYPE_PARAGRAPH) {
                            this->offset = prevElem->offset;
                        }
                    }
                }
            }
        }
        length = line.length() - offset;
        return true;
    }
    return false;
}

QString ParseElementParagraph::generateOpenHtml() const {
    if (isListSingleLine()) {
        return "";
    }
    if (this->isParagraphBegin()) {
        return "<p>";
    }
    return "";
}

QString ParseElementParagraph::generateCloseHtml() const {
    if (isListSingleLine()) {
        return "";
    }
    if (this->isParagraphEnd()) {
        return "</p>";
    }
    return "";
}

bool ParseElementParagraph::isParagraphBegin() const {
    if (parent->prev() == nullptr) {
        return true;
    }
    if (parent->prev()->getTypeAt(offset) != ParseElementType::TYPE_PARAGRAPH) {
        return true;
    }
    qint32 elemLen = parent->blocks.size();
    if (elemLen > 1) {
        auto prevElem = parent->blocks[elemLen - 2];
        if (prevElem->isBlockElement()) {
            auto prevBlock = qSharedPointerDynamicCast<ParseElementBlock>(prevElem);
            if (!prevBlock->isVirtual) {
                if (prevBlock->type() == ParseElementType::TYPE_LIST_ORDERED ||
                    prevBlock->type() == ParseElementType::TYPE_LIST_UNORDERED) {
                    return true;
                }
            }
        }
    }
    return false;
}

bool ParseElementParagraph::isParagraphEnd() const {
    if (parent->next() == nullptr) {
        return true;
    }
    if (parent->next()->getTypeAt(offset) != ParseElementType::TYPE_PARAGRAPH) {
        return true;
    }
    qint32 elemLen = parent->blocks.size();
    if (elemLen > 1) {
        auto prevElem = parent->blocks[elemLen - 2];
        if (prevElem->isBlockElement()) {
            auto prevBlock = qSharedPointerDynamicCast<ParseElementBlock>(prevElem);
            if (!prevBlock->isVirtual) {
                if (prevBlock->type() == ParseElementType::TYPE_LIST_ORDERED ||
                    prevBlock->type() == ParseElementType::TYPE_LIST_UNORDERED) {
                    if (parent->next()->getTypeAt(prevElem->offset) != prevElem->type()) {
                        return true;
                    }
                    auto nextElem = parent->next()->getElementAt(prevElem->offset);
                    if (nextElem->isBlockElement()) {
                        auto nextBlock = qSharedPointerDynamicCast<ParseElementBlock>(nextElem);
                        if (!nextBlock->isVirtual) {
                            return true;
                        }
                    }
                }
            }
        }
    }
    return false;
}

bool ParseElementParagraph::isListSingleLine() const {
    qint32 elemLen = parent->blocks.size();
    if (elemLen > 1) {
        auto prevElem = parent->blocks[elemLen - 2];
        if (prevElem->isBlockElement()) {
            auto prevBlock = qSharedPointerDynamicCast<ParseElementBlock>(prevElem);
            if (!prevBlock->isVirtual) {
                if (prevBlock->type() == ParseElementType::TYPE_LIST_ORDERED ||
                    prevBlock->type() == ParseElementType::TYPE_LIST_UNORDERED) {
                    ParseLineData* line = this->parent;
                    while (true) {
                        ParseLineData* next = line->next();
                        if (next == nullptr) {
                            return true;
                        }
                        if (next->blocks.size() != line->blocks.size()) {
                            return true;
                        }
                        qint32 blockLen = next->blocks.size();
                        for (qint32 i = 0; i < blockLen - 1; ++i) {
                            if (next->blocks[i]->type() != line->blocks[i]->type()) {
                                return true;
                            }
                            if (next->blocks[i]->offset != line->blocks[i]->offset) {
                                return true;
                            }
                            if (i < blockLen - 2) {
                                if (next->blocks[i]->isVirtual != line->blocks[i]->isVirtual) {
                                    return true;
                                }
                            }
                        }
                        if (next->blocks[blockLen - 2]->isVirtual == false) {
                            return true;
                        }
                        if (next->blocks[blockLen - 1]->type() == ParseElementType::TYPE_PARAGRAPH) {
                            return false;
                        }
                        line = next;
                    }
                }
            }
        }
    }
    return false;
}
