#include <algorithm>
#include "ParseElement.h"
#include "ParseElementBlock.h"
#include "ParseElementSpan.h"
#include "ParseElementParagraph.h"
#include "ParseLineData.h"

ParseLineData::ParseLineData() {
    this->_prev = nullptr;
    this->_next = nullptr;
    this->labelSet = nullptr;
}

ParseLineData::~ParseLineData() {
    this->removeFromList();
}

ParseLineData* ParseLineData::prev() const {
    return this->_prev;
}

ParseLineData* ParseLineData::next() const {
    return this->_next;
}

void ParseLineData::setNeighbor(ParseLineData* prevLine, ParseLineData* nextLine) {
    this->_prev = prevLine;
    this->_next = nextLine;
    if (prevLine != nullptr) {
        prevLine->_next = this;
    }
    if (nextLine != nullptr) {
        nextLine->_prev = this;
    }
}

void ParseLineData::removeFromList() {
    if (this->_prev != nullptr) {
        this->_prev->_next = this->_next;
    }
    if (this->_next != nullptr) {
        this->_next->_prev = this->_prev;
    }
    this->_prev = nullptr;
    this->_next = nullptr;
}

void ParseLineData::removeCurrentElements() {
    this->removeCurrentBlocks();
    this->removeCurrentSpans();
}

void ParseLineData::removeCurrentBlocks() {
    for (auto block : this->blocks) {
        block->remove();
    }
    this->blocks.clear();
}

void ParseLineData::removeCurrentSpans() {
    for (auto span : this->spans) {
        span->remove();
    }
    this->spans.clear();
}

void ParseLineData::saveLineStatus() {
    this->_oldBlocks = this->blocks;
}

bool ParseLineData::isLineStatusChanged() const {
    if (this->_oldBlocks.size() != this->blocks.size()) {
        return true;
    }
    qint32 len = this->blocks.size();
    for (qint32 i = 0; i < len; ++i) {
        if (this->_oldBlocks[i]->type() != this->blocks[i]->type() ||
            this->_oldBlocks[i]->offset != this->blocks[i]->offset) {
            return true;
        }
    }
    return false;
}

QString ParseLineData::generateHtml() const {
    QString html;
    QVector<OffsetElement> orders;
    for (auto span : spans) {
        OffsetElement order;
        order.elem = span;
        order.offset = span->offset;
        order.isOpen = true;
        orders.push_back(order);
        order.offset = span->offset + span->length - 1;
        order.isOpen = false;
        orders.push_back(order);
    }
    std::sort(orders.begin(), orders.end());
    for (auto it = blocks.begin(); it != blocks.end(); ++it) {
        QSharedPointer<ParseElement> element(*it);
        html += qSharedPointerDynamicCast<ParseElementBlock>(element)->generateOpenHtml();
    }
    for (auto order : orders) {
        if (order.isOpen) {
            if (order.elem->openActivate) {
                html += order.elem->generateOpenHtml();
            }
        }
        else {
            if (order.elem->closeActivate) {
                html += order.elem->generateCloseHtml();
            }
        }
    }
    for (qint32 i = blocks.size() - 1; i >= 0; --i) {
        html += qSharedPointerDynamicCast<ParseElementBlock>(blocks[i])->generateCloseHtml();
    }
    return html;
}

QSharedPointer<ParseElementBlock> ParseLineData::getElementAt(const qint32 offset) const {
    for (auto element : this->blocks) {
        if (element->offset == offset) {
            return element;
        } else if (element->offset > offset) {
            break;
        }
    }
    return QSharedPointer<ParseElementBlock>();
}

ParseElementType ParseLineData::getTypeAt(const qint32 offset) const {
    auto element = getElementAt(offset);
    if (element == nullptr) {
        return ParseElementType::TYPE_INVALID;
    }
    return element->type();
}

qint32 ParseLineData::getIndexAt(const qint32 offset) const {
    qint32 len = this->blocks.size();
    for (qint32 i = 0; i < len; ++i) {
        if (blocks[i]->offset == offset) {
            return i;
        } else if (blocks[i]->offset > offset) {
            break;
        }
    }
    return -1;
}

QSharedPointer<ParseElementBlock> ParseLineData::lastElement() const {
    if (this->blocks.size() > 0) {
        return this->blocks.last();
    }
    return QSharedPointer<ParseElementBlock>();
}

ParseElementType ParseLineData::lastType() const {
    if (this->blocks.size() > 0) {
        return this->blocks.last()->type();
    }
    return ParseElementType::TYPE_INVALID;
}
