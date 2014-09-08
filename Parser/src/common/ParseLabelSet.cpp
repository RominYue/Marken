#include "ParseElementLink.h"
#include "ParseElementLinkLabel.h"
#include "ParseLabelSet.h"

ParseLabelSet::ParseLabelSet() {
}

ParseLabelSet::~ParseLabelSet() {
}

void ParseLabelSet::addLinkLabel(ParseElementLinkLabel* linkLabel) {
    QString& label = linkLabel->label;
    QString& link = linkLabel->link;
    QString& title = linkLabel->title;
    this->_links[label].push_back(link);
    if (title.length() > 0) {
        this->_titles[label].push_back(title);
    }
}

void ParseLabelSet::addLinkTitle(ParseElementLinkLabel* linkLabel) {
    QString& label = linkLabel->label;
    QString& title = linkLabel->title;
    this->_titles[label].push_back(title);
}

void ParseLabelSet::removeLinkLabel(ParseElementLinkLabel* linkLabel) {
    QString& label = linkLabel->label;
    QString& link = linkLabel->link;
    QString& title = linkLabel->title;
    QList<QString>& links = this->_links[label];
    for (auto it = links.begin(); it != links.end(); ++it) {
        if ((*it) == link) {
            links.erase(it);
            break;
        }
    }
    QList<QString>& titles = this->_titles[label];
    for (auto it = titles.begin(); it != titles.end(); ++it) {
        if ((*it) == title) {
            titles.erase(it);
            break;
        }
    }
}

void ParseLabelSet::removeLinkTitle(ParseElementLinkLabel* linkLabel) {
    QString& label = linkLabel->label;
    QString& title = linkLabel->title;
    QList<QString>& titles = this->_titles[label];
    for (auto it = titles.begin(); it != titles.end(); ++it) {
        if ((*it) == title) {
            titles.erase(it);
            break;
        }
    }
}

void ParseLabelSet::addLinkElement(const QString& label, ParseElementLink* elem) {
    this->_elems[label].push_back(elem);
}

void ParseLabelSet::removeLinkElement(const QString& label, ParseElementLink* elem) {
    QList<ParseElementLink*>& elems = this->_elems[label];
    for (auto it = elems.begin(); it != elems.end(); ++it) {
        if ((*it) == elem) {
            elems.erase(it);
            break;
        }
    }
}

QString ParseLabelSet::getLink(const QString& label) {
    QList<QString>& links = this->_links[label];
    if (links.size() > 0) {
        return *links.begin();
    }
    return "";
}

QString ParseLabelSet::getTitle(const QString& label) {
    QList<QString>& titles = this->_titles[label];
    if (titles.size() > 0) {
        return *titles.begin();
    }
    return "";
}
