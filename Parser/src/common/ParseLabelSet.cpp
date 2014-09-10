#include "ParseElementLink.h"
#include "ParseElementLinkLabel.h"
#include "ParseLabelSet.h"

ParseLabelSet::ParseLabelSet() {
}

ParseLabelSet::~ParseLabelSet() {
}

void ParseLabelSet::addLinkLabel(ParseElementLinkLabel* linkLabel) {
    QString label = linkLabel->label.toLower();
    QString& link = linkLabel->link;
    QString& title = linkLabel->title;
    if (link.length() > 0) {
        this->_links[label] = link;
    }
    if (title.length() > 0) {
        this->_titles[label] = title;
    }
}

QString ParseLabelSet::getLink(const QString& label) {
    auto it = this->_links.find(label.toLower());
    if (it != this->_links.end()) {
        return it.value();
    }
    return "";
}

QString ParseLabelSet::getTitle(const QString& label) {
    auto it = this->_titles.find(label.toLower());
    if (it != this->_titles.end()) {
        return it.value();
    }
    return "";
}
