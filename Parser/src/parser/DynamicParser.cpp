#include "ParseElementBlock.h"
#include "ParseElementEmpty.h"
#include "ParseElementHtmlBlock.h"
#include "ParseElementCodeBlock.h"
#include "ParseElementCodeFence.h"
#include "ParseElementHeaderAtx.h"
#include "ParseElementHeaderSetext.h"
#include "ParseElementHorizontal.h"
#include "ParseElementListUnordered.h"
#include "ParseElementListOrdered.h"
#include "ParseElementQuote.h"
#include "ParseElementParagraph.h"
#include "ParseElementLinkLabel.h"
#include "ParseElementSpan.h"
#include "ParseElementFactory.h"
#include "ParseLineData.h"
#include "DynamicParser.h"

DynamicParser::DynamicParser() {
    this->_blocks.push_back(QSharedPointer<ParseElementBlock>(new ParseElementHtmlBlock()));
    this->_blocks.push_back(QSharedPointer<ParseElementBlock>(new ParseElementCodeFence()));
    this->_blocks.push_back(QSharedPointer<ParseElementBlock>(new ParseElementHeaderAtx()));
    this->_blocks.push_back(QSharedPointer<ParseElementBlock>(new ParseElementHeaderSetext()));
    this->_blocks.push_back(QSharedPointer<ParseElementBlock>(new ParseElementHorizontal()));
    this->_blocks.push_back(QSharedPointer<ParseElementBlock>(new ParseElementListUnordered()));
    this->_blocks.push_back(QSharedPointer<ParseElementBlock>(new ParseElementListOrdered()));
    this->_blocks.push_back(QSharedPointer<ParseElementBlock>(new ParseElementQuote()));
    this->_blocks.push_back(QSharedPointer<ParseElementBlock>(new ParseElementLinkLabel()));
    this->_blocks.push_back(QSharedPointer<ParseElementBlock>(new ParseElementCodeBlock()));
    this->_blocks.push_back(QSharedPointer<ParseElementBlock>(new ParseElementParagraph()));
}

DynamicParser::~DynamicParser() {
}

void DynamicParser::ParserLine(ParseLineData* data, QString line) {
    int offset = 0;
    int lineLength = line.size();
    ParseElementFactory factory;
    data->labelSet = &this->linkLabelSet;
    data->removeCurrentBlocks();
    bool stopParseList = false;
    bool stopInherit = false;
    while (offset < lineLength) {
        int length = -1;
        for (auto element : this->_blocks) {
            element->parent = data;
            element->offset = offset;
            if (element->stopParsing(offset)) {
                continue;
            }
            if (element->tryParse(line, offset, length)) {
                if (stopInherit) {
                    if (element->isVirtual) {
                        continue;
                    }
                }
                if (stopParseList) {
                    if (element->type() == ParseElementType::TYPE_LIST_ORDERED ||
                        element->type() == ParseElementType::TYPE_LIST_UNORDERED) {
                        if (!element->isVirtual) {
                            continue;
                        }
                    }
                }
                if (element->type() == ParseElementType::TYPE_LIST_ORDERED ||
                    element->type() == ParseElementType::TYPE_LIST_UNORDERED) {
                    if (!element->isVirtual) {
                        stopParseList = true;
                    }
                }
                element->text = line.mid(offset, length);
                element->length = length - offset;
                if (element->parent->prev() != nullptr) {
                    if (element->parent->prev()->blocks.size() > 0) {
                        if (element->parent->prev()->blocks.size() > data->blocks.size()) {
                            int index = data->blocks.size();
                            if (element->type() != data->prev()->blocks[index]->type() ||
                                element->offset != data->prev()->blocks[index]->offset ||
                                element->isVirtual != data->prev()->blocks[index]->isVirtual) {
                                stopInherit = true;
                            }
                        }
                    }
                }
                if (stopInherit) {
                    if (element->type() == ParseElementType::TYPE_PARAGRAPH) {
                        auto lastElem = data->lastElement();
                        if (lastElem != nullptr) {
                            if (lastElem->offset == offset && lastElem->isVirtual) {
                                data->blocks.pop_back();
                            }
                        }
                    }
                }
                data->blocks.push_back(factory.copy(element));
                offset += length;
                break;
            }
        }
        if (length == -1) {
            ++offset;
        }
    }
    if (data->prev() != nullptr) {
        int elemLen = data->blocks.size();
        int prevLen = data->prev()->blocks.size();
        if (elemLen < prevLen) {
            if (!stopInherit) {
                for (int i = elemLen; i < prevLen; ++i) {
                    if (data->prev()->blocks[i]->type() != ParseElementType::TYPE_PARAGRAPH) {
                        if (data->prev()->blocks[i]->inheritable()) {
                            auto elem = factory.copy(data->prev()->blocks[i]);
                            elem->parent = data;
                            elem->length = 0;
                            qSharedPointerDynamicCast<ParseElementBlock>(elem)->isVirtual = true;
                            data->blocks.push_back(elem);
                        }
                    } else {
                        QSharedPointer<ParseElementEmpty> elem(new ParseElementEmpty());
                        elem->parent = data;
                        elem->offset = data->prev()->blocks[i]->offset;
                        elem->offset = 0;
                        elem->length = 0;
                        elem->isVirtual = true;
                        data->blocks.push_back(qSharedPointerDynamicCast<ParseElementBlock>(elem));
                    }
                }
            }
        }
    }
    this->ParserSpan(data);
}

void DynamicParser::ParserSpan(ParseLineData* data) {
    this->_prevLineNum = 0;
    this->_nextLineNum = 0;
    if (data->blocks.size() > 0) {
        auto elem = data->lastElement();
        auto type = data->lastType();
        if (type == ParseElementType::TYPE_PARAGRAPH ||
            type == ParseElementType::TYPE_HEADER_ATX ||
            type == ParseElementType::TYPE_HEADER_SETEXT) {
            this->_spanParser.ParserElement(elem);
            this->_prevLineNum = this->_spanParser.prevLineNum();
            this->_nextLineNum = this->_spanParser.nextLineNum();
        } else {
            data->removeCurrentSpans();
        }
    }
}

int DynamicParser::prevLineNum() const {
    return this->_prevLineNum;
}

int DynamicParser::nextLineNum() const {
    return this->_nextLineNum;
}
