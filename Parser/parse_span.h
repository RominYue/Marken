#ifndef PARSE_SPAN_H
#define PARSE_SPAN_H

#include <vector>
#include <string>
#include <memory>
#include "parse.h"
#include "parse_elem_factory.h"
using std::vector;
using std::string;
using std::shared_ptr;

class ParseElement;
class ParseElementSpan;
class ParseElementParagraph;
class ParseElementHeader;
class ParseElementHeaderSetext;
class ParseLine;

class SpanParser : public Parser {
public:
    SpanParser();
    void parseElement(shared_ptr<ParseElement> elem);

    int prevLineNum() const;
    int nextLineNum() const;

private:
    int _prevLineNum;
    int _nextLineNum;

    ParseElementFactory _factory;
    vector<shared_ptr<ParseElementSpan>> _spans;
    void parseHeader(shared_ptr<ParseElementHeader> elem);
    void parseHeaderSetext(shared_ptr<ParseElementHeaderSetext> elem);
    void parseParagraphElement(shared_ptr<ParseElementParagraph> elem);
    vector<shared_ptr<ParseElementSpan>> parseLine(const string& line, int utf8Offset);
    vector<vector<shared_ptr<ParseElementSpan>>> parseParagraph(const vector<string>& paragraph);

    void initSpanParent(ParseLine* parent);
};

#endif // PARSE_SPAN_H
