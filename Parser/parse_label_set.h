#ifndef PARSE_LABEL_SET_H
#define PARSE_LABEL_SET_H

#include <map>
#include <list>
#include <string>
#include <memory>
using std::map;
using std::list;
using std::string;
using std::shared_ptr;
class ParseElementLink;
class ParseElementLinkLabel;

class ParseLabelSet {
public:
    ParseLabelSet();
    virtual ~ParseLabelSet();

    void addLinkLabel(ParseElementLinkLabel* linkLabel);
    void addLinkTitle(ParseElementLinkLabel* linkLabel);
    void removeLinkLabel(ParseElementLinkLabel* linkLabel);
    void removeLinkTitle(ParseElementLinkLabel* linkLabel);

    void addLinkElement(const string& label, ParseElementLink* elem);
    void removeLinkElement(const string& label, ParseElementLink* elem);

    string getLink(const string& label);
    string getTitle(const string& label);

private:
    map<string, list<string>> _links;
    map<string, list<string>> _titles;
    map<string, list<ParseElementLink*>> _elems;
};

#endif // PARSE_LABEL_SET_H
