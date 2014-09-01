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

class SpanParser : public Parser {
public:
    SpanParser();
    void parseElement(shared_ptr<ParseElement> elem);

private:
    ParseElementFactory _factory;
    vector<shared_ptr<ParseElementSpan>> _spans;
    void parseInlineElement(shared_ptr<ParseElement> elem);
    void parseParagraphElement(shared_ptr<ParseElementParagraph> elem);
    vector<shared_ptr<ParseElementSpan>> parseLine(const string& line, int utf8Offset);
    vector<vector<shared_ptr<ParseElementSpan>>> parseParagraph(const vector<string>& paragraph);
};

#endif // PARSE_SPAN_H
