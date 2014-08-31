#include "parse_elem.h"
#include "parse_elem_span.h"
#include "parse_elem_paragraph.h"
#include "parse_line.h"
#include "parse_elem_escape.h"
#include "parse_elem_amp.h"
#include "parse_elem_code_inline.h"
#include "parse_elem_emphasis.h"
#include "parse_elem_strong.h"
#include "parse_elem_html_inline.h"
#include "parse_elem_link_inline.h"
#include "parse_elem_link_label.h"
#include "parse_elem_link_reference.h"
#include "parse_elem_image.h"
#include "parse_elem_factory.h"
#include "parse_span.h"
using namespace std;

SpanParser::SpanParser() : Parser() {
    this->_spans.push_back(shared_ptr<ParseElementSpan>(new ParseElementEscape()));
    this->_spans.push_back(shared_ptr<ParseElementSpan>(new ParseElementAmp()));
    this->_spans.push_back(shared_ptr<ParseElementSpan>(new ParseElementCodeInline()));
    this->_spans.push_back(shared_ptr<ParseElementSpan>(new ParseElementEmphasis()));
    this->_spans.push_back(shared_ptr<ParseElementSpan>(new ParseElementStrong()));
    this->_spans.push_back(shared_ptr<ParseElementSpan>(new ParseElementHtmlInline()));
    this->_spans.push_back(shared_ptr<ParseElementSpan>(new ParseElementLinkInline()));
    this->_spans.push_back(shared_ptr<ParseElementSpan>(new ParseElementLinkLabel()));
    this->_spans.push_back(shared_ptr<ParseElementSpan>(new ParseElementLinkReference()));
    this->_spans.push_back(shared_ptr<ParseElementSpan>(new ParseElementImage()));
}

vector<shared_ptr<ParseElementSpan>> SpanParser::parseElement(shared_ptr<ParseElement> elem) {
    if (elem->type() == ParseElementType::TYPE_PARAGRAPH) {
        return this->parseParagraphElement(dynamic_pointer_cast<ParseElementParagraph>(elem));
    }
    return this->parseInlineElement(elem);
}

vector<shared_ptr<ParseElementSpan>> SpanParser::parseInlineElement(shared_ptr<ParseElement> elem) {
    auto text = elem->inlineText();
    auto spans = this->parseLine(text);
    auto wordCount = this->getUtf8CharacterCount(text);
    for (auto span : spans) {
        span->utf8Offset += elem->utf8Offset;
    }
    return spans;
}

vector<shared_ptr<ParseElementSpan>> SpanParser::parseParagraphElement(shared_ptr<ParseElementParagraph> elem) {
    auto begin = elem;
    while (!begin->isParagraphBegin()) {
        begin = dynamic_pointer_cast<ParseElementParagraph>(*(begin->parent->prev()->blocks.rbegin()));
    }
    vector<string> paragraph;
    auto end = begin;
    while (!end->isParagraphEnd()) {
        paragraph.push_back(end->inlineText());
        end = dynamic_pointer_cast<ParseElementParagraph>(*(end->parent->next()->blocks.rbegin()));
    }
    vector<shared_ptr<ParseElementSpan>> spans;
    auto spanVec = this->parseParagraph(paragraph);
    end = begin;
    int index = 0;
    while (!end->isParagraphEnd()) {
        for (auto span : spanVec[index]) {
            span->utf8Offset += end->utf8Offset;
            spans.push_back(span);
        }
        end = dynamic_pointer_cast<ParseElementParagraph>(*(end->parent->next()->blocks.rbegin()));
    }
    return spans;
}

vector<shared_ptr<ParseElementSpan>> SpanParser::parseLine(const string& line) {
    vector<shared_ptr<ParseElementSpan>> spans;
    int offset = 0;
    int lineLen = line.length();
    while (offset < lineLen) {
        for (auto elem : this->_spans) {
            int length = elem->tryParse(line, offset);
            if (length > 0) {
                elem->offset = offset;
                elem->length = length;
                spans.push_back(this->_factory.copy(elem));
                offset += length;
            }
        }
    }
    return spans;
}

vector<vector<shared_ptr<ParseElementSpan>>> SpanParser::parseParagraph(const vector<string>& paragraph) {
    string line;
    int lineNum = paragraph.size();
    vector<int> lengths;
    vector<vector<shared_ptr<ParseElementSpan>>> spanVec;
    lengths.push_back(0);
    for (auto p : paragraph) {
        line += p;
        spanVec.push_back(vector<shared_ptr<ParseElementSpan>>());
        lengths.push_back((int)p.length());
    }
    for (int i = 1; i < lineNum; ++i) {
        lengths[i] += lengths[i - 1];
    }
    auto spans = this->parseLine(line);
    for (auto span : spans) {
        int offset = span->offset;
        int length = span->length;
        int start = lineNum - 1;
        for (int i = 1; i <= lineNum; ++i) {
            if (offset < lengths[i]) {
                start = i;
                break;
            }
        }
        int end = lineNum - 1;
        for (int i = 1; i <= lineNum; ++i) {
            if (offset + length <= lengths[i]) {
                end = i;
                break;
            }
        }
        if (start == end) {
            span->offset = span->offset - lengths[start - 1];
            spanVec[start].push_back(this->_factory.copy(span));
        } else {
            span->offset = span->offset - lengths[start - 1];
            span->length = lengths[start] - span->offset;
            spanVec[start].push_back(this->_factory.copy(span));
            for (int i = start + 1; i <= end - 1; ++i) {
                span->offset = 0;
                span->length = lengths[i] - lengths[i - 1];
                spanVec[i].push_back(this->_factory.copy(span));
            }
            span->offset = 0;
            span->length = span->offset - lengths[end - 1];
            spanVec[end].push_back(this->_factory.copy(span));
        }
    }
    return spanVec;
}
