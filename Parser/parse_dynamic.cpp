#include "parse_elem_block.h"
#include "parse_elem_html_block.h"
#include "parse_elem_code_block.h"
#include "parse_elem_span.h"
#include "parse_elem_factory.h"
#include "parse_line.h"
#include "parse_dynamic.h"
using namespace std;

DynamicParser::DynamicParser() {
    this->_reparseEvent = nullptr;
    this->_blockElements.push_back(shared_ptr<ParseElementBlock>(new ParseElementHtmlBlock()));
    this->_blockElements.push_back(shared_ptr<ParseElementBlock>(new ParseElementCodeBlock()));
}

DynamicParser::~DynamicParser() {
}

static int isUtf8CharacterBegin(char ch) {
    return ((ch & 0x80) == 0) || ((ch & 0xC0) == 0xC0);
}

void DynamicParser::parseLine(ParseLine* data, string line) {
    vector<int> wordCount;
	wordCount.push_back(0);
    for (auto ch : line) {
        int last = 0;
        if (wordCount.size() > 0) {
            last = *wordCount.rbegin();
        }
        if (isUtf8CharacterBegin(ch)) {
            wordCount.push_back(last + 1);
        }
    }
    int offset = 0;
    int lineLength = line.size();
    ParseElementFactory factory;
    while (offset < lineLength) {
        int length = -1;
        for (auto element : this->_blockElements) {
            element->parent = data;
            element->offset = offset;
            if (element->tryParse(line, offset, length)) {
                element->text = line.substr(offset, length);
                element->utf8Offset = wordCount[offset];
                element->utf8Length = wordCount[offset + length] - wordCount[offset];
                data->elements.push_back(factory.copy(element));
                offset += length;
                continue;
            }
        }
        if (length == -1) {
            break;
        }
    }
}

void DynamicParser::setReparseEvent(function<void(vector<ParseLine>&)> event) {
    this->_reparseEvent = event;
}
