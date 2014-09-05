#include "parse_elem_block.h"
#include "parse_elem_empty.h"
#include "parse_elem_html_block.h"
#include "parse_elem_code_block.h"
#include "parse_elem_header_atx.h"
#include "parse_elem_header_setext.h"
#include "parse_elem_horizontal.h"
#include "parse_elem_list_unordered.h"
#include "parse_elem_list_ordered.h"
#include "parse_elem_quote.h"
#include "parse_elem_paragraph.h"
#include "parse_elem_link_label.h"
#include "parse_elem_span.h"
#include "parse_elem_factory.h"
#include "parse_line.h"
#include "parse_dynamic.h"
using namespace std;

DynamicParser::DynamicParser() : Parser() {
    this->_blocks.push_back(shared_ptr<ParseElementBlock>(new ParseElementHtmlBlock()));
    this->_blocks.push_back(shared_ptr<ParseElementBlock>(new ParseElementCodeBlock()));
    this->_blocks.push_back(shared_ptr<ParseElementBlock>(new ParseElementHeaderAtx()));
    this->_blocks.push_back(shared_ptr<ParseElementBlock>(new ParseElementHeaderSetext()));
    this->_blocks.push_back(shared_ptr<ParseElementBlock>(new ParseElementHorizontal()));
    this->_blocks.push_back(shared_ptr<ParseElementBlock>(new ParseElementListUnordered()));
    this->_blocks.push_back(shared_ptr<ParseElementBlock>(new ParseElementListOrdered()));
    this->_blocks.push_back(shared_ptr<ParseElementBlock>(new ParseElementQuote()));
    this->_blocks.push_back(shared_ptr<ParseElementBlock>(new ParseElementLinkLabel()));
    this->_blocks.push_back(shared_ptr<ParseElementBlock>(new ParseElementParagraph()));
}

DynamicParser::~DynamicParser() {
}

void DynamicParser::parseLine(ParseLine* data, string line) {
    auto wordCount = this->getUtf8CharacterCount(line);
    int offset = 0;
    int lineLength = line.size();
    ParseElementFactory factory;
    data->labelSet = &this->_linkLabelSet;
    data->removeCurrentBlocks();
    bool stopInherit = false;
    while (offset < lineLength) {
        int length = -1;
        for (auto element : this->_blocks) {
            element->parent = data;
            element->offset = offset;
            if (element->tryParse(line, offset, length)) {
                if (stopInherit) {
                    if (element->isVirtual) {
                        continue;
                    }
                }
                element->text = line.substr(offset, length);
                element->utf8Offset = wordCount[offset];
                element->utf8Length = wordCount[offset + length] - wordCount[offset];
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
                        if (data->blocks.size() > 0) {
                            if ((*data->blocks.rbegin())->offset == offset &&
                                (*data->blocks.rbegin())->isVirtual) {
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
                            elem->utf8Length = 0;
                            dynamic_pointer_cast<ParseElementBlock>(elem)->isVirtual = true;
                            data->blocks.push_back(elem);
                        }
                    } else {
                        shared_ptr<ParseElementEmpty> elem(new ParseElementEmpty());
                        elem->parent = data;
                        elem->offset = data->prev()->blocks[i]->offset;
                        elem->utf8Offset = 0;
                        elem->utf8Length = 0;
                        elem->isVirtual = true;
                        data->blocks.push_back(dynamic_pointer_cast<ParseElementBlock>(elem));
                    }
                }
            }
        }
    }
    if (data->blocks.size() > 0) {
        auto elem = *data->blocks.rbegin();
        auto type = (*data->blocks.rbegin())->type();
        if (type == ParseElementType::TYPE_PARAGRAPH) {
            this->_spanParser.parseElement(elem);
        } else if (type == ParseElementType::TYPE_HEADER_ATX ||
                   type == ParseElementType::TYPE_HEADER_SETEXT) {
            this->_spanParser.parseElement(elem);
        }
    }
}

ParseLine* DynamicParser::firstParseLine() {
    return this->_spanParser.firstParseLine();
}

ParseLine* DynamicParser::lastParseLine() {
    return this->_spanParser.lastParseLine();
}
