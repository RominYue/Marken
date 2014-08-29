#ifndef PARSE_DYNAMIC_H
#define PARSE_DYNAMIC_H

#include <string>
#include <vector>
#include <memory>
#include <functional>
using std::string;
using std::vector;
using std::shared_ptr;
using std::function;

class ParseLine;
class ParseElementBlock;
class Parseblockspan;

class DynamicParser {
public:
    DynamicParser();
    virtual ~DynamicParser();
    void parseLine(ParseLine* data, string line);
    void setReparseEvent(function<void(vector<ParseLine>&)> event);
private:
    function<void(vector<ParseLine>&)> _reparseEvent;
    vector<shared_ptr<ParseElementBlock>> _blockblocks;
    vector<shared_ptr<Parseblockspan>> _spanblocks;
};

#endif // PARSE_DYNAMIC_H
