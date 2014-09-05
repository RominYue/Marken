#ifndef PARSE_DYNAMIC_H
#define PARSE_DYNAMIC_H

#include <string>
#include <vector>
#include <memory>
#include <functional>
#include "parse.h"
#include "parse_span.h"
#include "parse_label_set.h"
using std::string;
using std::vector;
using std::shared_ptr;
using std::function;

class ParseLine;
class ParseElementBlock;
class ParseElementLinkLabel;
class ParseLabelSet;

class DynamicParser : public Parser {
public:
    DynamicParser();
    virtual ~DynamicParser();
    void parseLine(ParseLine* data, string line);

    ParseLine* firstParseLine();
    ParseLine* lastParseLine();

private:
    SpanParser _spanParser;
    vector<shared_ptr<ParseElementBlock>> _blocks;
    ParseLabelSet _linkLabelSet;
};

#endif // PARSE_DYNAMIC_H
