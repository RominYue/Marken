#ifndef PARSE_SPAN_H
#define PARSE_SPAN_H

#include <vector>
#include <string>
#include <memory>
#include "parse.h"
using std::vector;
using std::string;
using std::shared_ptr;

class ParseElement;
class ParseElementSpan;
class ParseElementParagraph;
class ParseElementFactory;

class SpanParser : public Parser {
public:
    SpanParser();
    vector<shared_ptr<ParseElementSpan>> parseElement(shared_ptr<ParseElement> elem);

private:
    ParseElementFactory _factory;
    vector<shared_ptr<ParseElementSpan>> _spans;
    vector<shared_ptr<ParseElementSpan>> parseInlineElement(shared_ptr<ParseElement> elem);
    vector<shared_ptr<ParseElementSpan>> parseParagraphElement(shared_ptr<ParseElementParagraph> elem);
    vector<shared_ptr<ParseElementSpan>> parseLine(const string& line);
    vector<vector<shared_ptr<ParseElementSpan>>> parseParagraph(const vector<string>& paragraph);
};

#endif // PARSE_SPAN_H
