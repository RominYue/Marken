#ifndef PARSE_DYNAMIC_H
#define PARSE_DYNAMIC_H

#include <string>
#include <vector>
#include <memory>
#include <functional>
#include "parse.h"
#include "parse_span.h"
using std::string;
using std::vector;
using std::shared_ptr;
using std::function;

class ParseLine;
class ParseElementBlock;
class Parseblockspan;

class DynamicParser : public Parser {
public:
    DynamicParser();
    virtual ~DynamicParser();
    void parseLine(ParseLine* data, string line);
    void setReparseEvent(function<void(vector<ParseLine>&)> event);
private:
    SpanParser _spanParser;
    function<void(vector<ParseLine>&)> _reparseEvent;
    vector<shared_ptr<ParseElementBlock>> _blocks;
};

#endif // PARSE_DYNAMIC_H
