#include "parse_elem_link.h"
#include "parse_elem_link_label.h"
#include "parse_label_set.h"
using namespace std;

ParseLabelSet::ParseLabelSet() {
}

ParseLabelSet::~ParseLabelSet() {
}

void ParseLabelSet::addLinkLabel(ParseElementLinkLabel* linkLabel) {
    string& label = linkLabel->label;
    string& link = linkLabel->link;
    string& title = linkLabel->title;
    this->_links[label].push_back(link);
    if (title.length() > 0) {
        this->_titles[label].push_back(title);
    }
}

void ParseLabelSet::addLinkTitle(ParseElementLinkLabel* linkLabel) {
    string& label = linkLabel->label;
    string& title = linkLabel->title;
    this->_titles[label].push_back(title);
}

void ParseLabelSet::removeLinkLabel(ParseElementLinkLabel* linkLabel) {
    string& label = linkLabel->label;
    string& link = linkLabel->link;
    string& title = linkLabel->title;
    list<string>& links = this->_links[label];
    for (auto it = links.begin(); it != links.end(); ++it) {
        if ((*it) == link) {
            links.erase(it);
            break;
        }
    }
    list<string>& titles = this->_titles[label];
    for (auto it = titles.begin(); it != titles.end(); ++it) {
        if ((*it) == title) {
            titles.erase(it);
            break;
        }
    }
}

void ParseLabelSet::removeLinkTitle(ParseElementLinkLabel* linkLabel) {
    string& label = linkLabel->label;
    string& title = linkLabel->title;
    list<string>& titles = this->_titles[label];
    for (auto it = titles.begin(); it != titles.end(); ++it) {
        if ((*it) == title) {
            titles.erase(it);
            break;
        }
    }
}

void ParseLabelSet::addLinkElement(const string& label, ParseElementLink* elem) {
    this->_elems[label].push_back(elem);
}

void ParseLabelSet::removeLinkElement(const string& label, ParseElementLink* elem) {
    list<ParseElementLink*>& elems = this->_elems[label];
    for (auto it = elems.begin(); it != elems.end(); ++it) {
        if ((*it) == elem) {
            elems.erase(it);
            break;
        }
    }
}

string ParseLabelSet::getLink(const string& label) {
    list<string>& links = this->_links[label];
    if (links.size() > 0) {
        return *links.begin();
    }
    return "";
}

string ParseLabelSet::getTitle(const string& label) {
    list<string>& titles = this->_titles[label];
    if (titles.size() > 0) {
        return *titles.begin();
    }
    return "";
}
