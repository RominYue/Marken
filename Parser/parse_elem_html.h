#ifndef PARSE_ELEM_HTML_H
#define PARSE_ELEM_HTML_H

#include <string>
using std::string;

class ParseElementHtml {
public:
    ParseElementHtml();

    const string& tag() const;
    void setTag(const string& val);

protected:
    enum Status {
        STATUS_BEGIN,
        STATUS_LT,
        STATUS_SLASH,
        STATUS_TAG,
        STATUS_SPACE_SUF,
        STATUS_ATTRIBUTE,
        STATUS_STRING,
        STATUS_ESCAPE,
        STATUS_GT
    };
    string _tag;
    bool findOpenTagOffset(const string &line, int &index);
    bool findCloseTagOffset(const string &line, int &index);
    bool matchToTagEnd(const string &line, int &index);
    bool matchToGt(const string &line, int &index);
    bool matchToEnd(const string &line, int &index);
};

#endif // PARSE_ELEM_HTML_H
