#include "MarkdownRegex.h"
#include "MarkdownBlockData.h"

MarkdownBlockData::MarkdownBlockData() : QTextBlockUserData() {
    this->clear();
}

void MarkdownBlockData::clear() {
    this->_types.clear();
    this->_indents.clear();
    this->_lastIndent = 0;
    this->_htmlTag.clear();
}

MarkdownBlockData::LineType MarkdownBlockData::type(int index) const {
    if (index >= this->_types.size()) {
        return LINE_INVALID;
    }
    return this->_types[index];
}

int MarkdownBlockData::indent(int index) const {
    if (index >= this->_indents.size()) {
        return -1;
    }
    return this->_indents[index];
}

QVector<MarkdownBlockData::LineType>* MarkdownBlockData::types() {
    return &this->_types;
}

QVector<int>* MarkdownBlockData::indents() {
    return &this->_indents;
}

int MarkdownBlockData::lastIndent() const {
    return this->_lastIndent;
}

void MarkdownBlockData::setLastIndent(int indent) {
    this->_lastIndent = indent;
}

void MarkdownBlockData::setHtmlTag(const QString &tag) {
    this->_htmlTag = tag.toLower();
}

const QString& MarkdownBlockData::htmlTag() const {
    return this->_htmlTag;
}

void MarkdownBlockData::recordState() {
    this->_lastTypes = this->_types;
    this->_lastIndents = this->_indents;
    this->_lastLastIndent = this->_lastIndent;
}

bool MarkdownBlockData::isStateChanged() const {
    if (this->_lastTypes.size() != this->_types.size()) {
        return true;
    }
    for (int i = 0; i < this->_types.size(); ++i) {
        if (this->_lastTypes[i] != this->_types[i]) {
            return true;
        }
    }
    for (int i = 0; i < this->_indents.size(); ++i) {
        if (this->_lastIndents[i] != this->_indents[i]) {
            return true;
        }
    }
    return this->_lastLastIndent != this->_lastIndent;
}
