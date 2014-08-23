#include "MarkdownBlockData.h"

MarkdownBlockData::MarkdownBlockData() : QTextBlockUserData() {
}

QVector<MarkdownBlockData::LineType>* MarkdownBlockData::types() {
    return &this->_types;
}

MarkdownBlockData::LineType MarkdownBlockData::firstType() const {
    return this->_types.first();
}

MarkdownBlockData::LineType MarkdownBlockData::lastType() const {
    return this->_types.last();
}

void MarkdownBlockData::setHtmlTag(const QString &tag) {
    this->_htmlTag = tag.toLower();
}

const QString& MarkdownBlockData::htmlTag() const {
    return this->_htmlTag;
}
