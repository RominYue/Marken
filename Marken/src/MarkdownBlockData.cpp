#include "MarkdownRegex.h"
#include "MarkdownBlockData.h"

MarkdownBlockData::MarkdownBlockData() : QTextBlockUserData() {
}

MarkdownBlockData::LineType MarkdownBlockData::type() const {
    return this->_type;
}


void MarkdownBlockData::setType(LineType type) {
    this->_type = type;
}

void MarkdownBlockData::setHtmlTag(const QString &tag) {
    this->_htmlTag = tag.toLower();
}

const QString& MarkdownBlockData::htmlTag() const {
    return this->_htmlTag;
}

