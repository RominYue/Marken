#include "parse_elem.h"
#include "parse_elem_span.h"
#include "parse_elem_paragraph.h"
#include "parse_line.h"
#include "parse_elem_plain.h"
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

void SpanParser::parseElement(shared_ptr<ParseElement> elem) {
    if (elem->type() == ParseElementType::TYPE_PARAGRAPH) {
        this->parseParagraphElement(dynamic_pointer_cast<ParseElementParagraph>(elem));
    } else if (elem->type() == ParseElementType::TYPE_HEADER_SETEXT) {
        if (elem->parent->prev() != nullptr) {
            if (elem->parent->prev()->blocks.size() > 0) {
                if ((*elem->parent->prev()->blocks.rbegin())->type() == ParseElementType::TYPE_HEADER_SETEXT) {
                    elem->parent->prev()->spans.clear();
                }
            }
        }
    } else {
        this->parseInlineElement(elem);
    }
}

void SpanParser::parseInlineElement(shared_ptr<ParseElement> elem) {
    auto text = elem->inlineText();
    auto spans = this->parseLine(text, 0);
    auto wordCount = this->getUtf8CharacterCount(text);
    for (auto span : spans) {
        span->utf8Offset += elem->utf8Offset;
    }
    // TODO
}

void SpanParser::parseParagraphElement(shared_ptr<ParseElementParagraph> elem) {
    auto begin = elem;
    while (!begin->isParagraphBegin()) {
        begin = dynamic_pointer_cast<ParseElementParagraph>(*(begin->parent->prev()->blocks.rbegin()));
    }
    vector<string> paragraph;
    auto end = begin;
    while (!end->isParagraphEnd()) {
        paragraph.push_back(end->text);
        end = dynamic_pointer_cast<ParseElementParagraph>(*(end->parent->next()->blocks.rbegin()));
    }
    paragraph.push_back(end->text);
    auto spanVec = this->parseParagraph(paragraph);
    end = begin;
    int index = 0;
    while (!end->isParagraphEnd()) {
        for (auto span : spanVec[index]) {
            span->utf8Offset += end->utf8Offset;
        }
        end->parent->spans = spanVec[index];
        end = dynamic_pointer_cast<ParseElementParagraph>(*(end->parent->next()->blocks.rbegin()));
        ++index;
    }
    for (auto span : spanVec[index]) {
        span->utf8Offset += end->utf8Offset;
    }
    end->parent->spans = spanVec[index];
}

vector<shared_ptr<ParseElementSpan>> SpanParser::parseLine(const string& line, int utf8Offset) {
    vector<shared_ptr<ParseElementSpan>> spans;
    vector<int> wordCnt = this->getUtf8CharacterCount(line);
    int last = 0, offset = 0;
    int lineLen = line.length();
    while (offset < lineLen) {
        bool flag = true;
        for (auto elem : this->_spans) {
            int length = elem->tryParse(line, offset);
            if (length > 0) {
                flag = false;
                if (offset > last) {
                    shared_ptr<ParseElementPlain> plainText(new ParseElementPlain());
                    plainText->offset = last;
                    plainText->utf8Offset = utf8Offset + wordCnt[last];
                    plainText->utf8Length = wordCnt[offset] - wordCnt[last];
                    plainText->text = line.substr(last, offset - last);
                    spans.push_back(plainText);
                }
                elem->utf8Offset = utf8Offset + wordCnt[offset];
                elem->utf8Length = wordCnt[offset + length] - wordCnt[offset];
                elem->text = line.substr(offset, length);
                spans.push_back(this->_factory.copy(elem));
                auto text = elem->inlineText();
                if (text.length() > 0) {
                    auto elems = this->parseLine(text, utf8Offset + wordCnt[offset + elem->inlineOffset]);
                    for (auto subElem : elems) {
                        spans.push_back(subElem);
                    }
                }
                offset += length;
                last = offset;
                break;
            }
        }
        if (flag) {
            ++offset;
        }
    }
    if (offset > last) {
        shared_ptr<ParseElementPlain> plainText(new ParseElementPlain());
        plainText->offset = last;
        plainText->utf8Offset = utf8Offset + wordCnt[last];
        plainText->utf8Length = wordCnt[offset] - wordCnt[last];
        plainText->text = line.substr(last, offset - last);
        spans.push_back(plainText);
    }
    return spans;
}

vector<vector<shared_ptr<ParseElementSpan>>> SpanParser::parseParagraph(const vector<string>& paragraph) {
    string line;
    int lineNum = paragraph.size();
    vector<int> lengths;
    vector<int> utf8Lengths;
    vector<vector<int>> wordNums;
    vector<vector<shared_ptr<ParseElementSpan>>> spanVec;
    lengths.push_back(0);
    utf8Lengths.push_back(0);
    for (auto p : paragraph) {
        line += p;
        spanVec.push_back(vector<shared_ptr<ParseElementSpan>>());
        wordNums.push_back(this->getUtf8CharacterCount(p));
        lengths.push_back((int)p.length());
        utf8Lengths.push_back(*wordNums.rbegin()->rbegin());
    }
    for (int i = 1; i <= lineNum; ++i) {
        lengths[i] += lengths[i - 1];
        utf8Lengths[i] += utf8Lengths[i - 1];
    }
    auto spans = this->parseLine(line, 0);
    for (auto span : spans) {
        int utf8Offset = span->utf8Offset;
        int utf8Length = span->utf8Length;
        int start = lineNum - 1;
        for (int i = 1; i <= lineNum; ++i) {
            if (utf8Offset < utf8Lengths[i]) {
                start = i;
                break;
            }
        }
        int end = lineNum - 1;
        for (int i = 1; i <= lineNum; ++i) {
            if (utf8Offset + utf8Length <= utf8Lengths[i]) {
                end = i;
                break;
            }
        }
        if (start == end) {
            span->openActivate = true;
            span->closeActivate = true;
            span->utf8Offset = span->utf8Offset - utf8Lengths[start - 1];
            spanVec[start - 1].push_back(this->_factory.copy(span));
        } else {
            string text = "";
            if (span->type() == ParseElementType::TYPE_PLAIN) {
                text = span->text;
            }
            span->openActivate = true;
            span->closeActivate = false;
            span->utf8Offset = span->utf8Offset - utf8Lengths[start - 1];
            span->utf8Length = utf8Lengths[start] - span->utf8Offset;
            if (span->type() == ParseElementType::TYPE_PLAIN) {
                span->text = text.substr(0, lengths[start] - span->offset);
            }
            spanVec[start - 1].push_back(this->_factory.copy(span));
            for (int i = start + 1; i < end; ++i) {
                span->openActivate = false;
                span->closeActivate = false;
                span->utf8Offset = 0;
                span->utf8Length = utf8Lengths[i] - utf8Lengths[i - 1];
                if (span->type() == ParseElementType::TYPE_PLAIN) {
                    span->text = text.substr(lengths[i - 1] - span->offset, lengths[i] - lengths[i - 1]);
                }
                spanVec[i - 1].push_back(this->_factory.copy(span));
            }
            span->openActivate = false;
            span->closeActivate = true;
            span->utf8Offset = 0;
            span->utf8Length = span->utf8Offset + span->utf8Length - utf8Lengths[end - 1];
            if (span->type() == ParseElementType::TYPE_PLAIN) {
                span->text = text.substr(lengths[end - 1] - span->offset, span->offset + text.length() - lengths[end - 1]);
            }
            spanVec[end - 1].push_back(this->_factory.copy(span));
        }
    }
    return spanVec;
}
