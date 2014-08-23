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

void MarkdownBlockData::setType(LineType type) {
    this->_types.clear();
    this->_types.append(type);
}

void MarkdownBlockData::setHtmlTag(const QString &tag) {
    this->_htmlTag = tag.toLower();
}

const QString& MarkdownBlockData::htmlTag() const {
    return this->_htmlTag;
}

void MarkdownBlockData::setHtml(const QString &html) {
    this->_html = html;
}

const QString& MarkdownBlockData::html() const {
    return this->_html;
}

void MarkdownBlockData::setText(const QString &text) {
    this->_text = text;
}

const QString& MarkdownBlockData::text() const {
    return this->_text;
}

void MarkdownBlockData::generateHtml() {
    switch (this->firstType()) {
    case LINE_BLOCK_HTML:
    case LINE_BLOCK_HTML_END:
        this->_html = this->_text;
        break;
    case LINE_CODE_BLOCK_SINGLE:
        this->_html = "<pre><code>" + removeCodeIndent(translate(this->_text)) + "</code></pre>";
        break;
    case LINE_CODE_BLOCK_BEGIN:
        this->_html = "<pre><code>" + removeCodeIndent(translate(this->_text)) + "<br>";
        break;
    case LINE_CODE_BLOCK_MID:
        this->_html = removeCodeIndent(translate(this->_text)) + "<br>";
        break;
    case LINE_CODE_BLOCK_END:
        this->_html = removeCodeIndent(translate(this->_text)) + "</code></pre>";
        break;
    default:
        this->_html = this->_text;
    }
}

QString MarkdownBlockData::removeCodeIndent(const QString &str) {
    if (str[0] == '\t') {
        return str.right(str.length() - 1);
    }
    return str.right(str.length() - 4);
}

QString MarkdownBlockData::translate(const QString &str) {
    QString trans;
    for (int i = 0; i < str.length(); ++i) {
        if (str[i] == '<') {
            trans += "&lt;";
        } else if (str[i] == '>') {
            trans += "&gt;";
        } else if (str[i] == '&') {
            trans += "&amp;";
        } else {
            trans += str[i];
        }
    }
    return trans;
}
