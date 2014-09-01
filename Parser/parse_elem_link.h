#ifndef PARSE_ELEM_LINKS_H
#define PARSE_ELEM_LINKS_H

#include "parse_elem_span.h"

class ParseElementLink : public ParseElementSpan {
public:
    ParseElementLink();

protected:
    enum Status {
        STATUS_BEGIN,
        STATUS_LEFT,
        STATUS_TEXT,
        STATUS_ESCAPE,
        STATUS_RIGHT,
    };
    bool parseOpenClose(const string& text, int& index, string& inner, char open, char close);
    bool parseBrackets(const string& text, int& index, string& inner);
    bool parseParentheses(const string& text, int& index, string& inner);

    string getCleanedTitle(const string& title) const;
};

#endif // PARSE_ELEM_LINKS_H
