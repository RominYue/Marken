#include "parse_elem.h"
#include "parse_elem_span.h"
#include "parse_elem_paragraph.h"
#include "parse_line.h"
#include "parse_span.h"
using namespace std;

SpanParser::SpanParser() : Parser() {
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
    // TODO
    return spans;
}

vector<vector<shared_ptr<ParseElementSpan>>> SpanParser::parseParagraph(const vector<string>& paragraph) {
    string line;
    for (auto p : paragraph) {
        line += p;
    }
    auto spans = this->parseLine(line);
    vector<vector<shared_ptr<ParseElementSpan>>> spanVec;
    // TODO
    return spanVec;
}
