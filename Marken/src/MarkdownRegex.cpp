#include "MarkdownRegex.h"

MarkdownRegex::MarkdownRegex() {
    this->initRegex();
}

const QMap<MarkdownDefine::SyntaxType, QRegExp>& MarkdownRegex::regex() const {
    return this->_regex;
}

const QRegExp& MarkdownRegex::regex(MarkdownDefine::SyntaxType name) const {
    if (this->_regex.contains(name)) {
        return this->_regex.find(name).value();
    }
    return this->_matchEmpty;
}

const QRegExp& MarkdownRegex::empty() const {
    return this->_matchEmpty;
}

void MarkdownRegex::initRegex() {
    this->_matchEmpty = QRegExp("^$");
    this->_regex[MarkdownDefine::INLINE_LINK] = QRegExp("\\[(.*)\\]\\s?\\(([^\\s]+)(.*)\\)");
    this->_regex[MarkdownDefine::INLINE_LINK].setMinimal(true);
    this->_regex[MarkdownDefine::REFERENCE_LINK] = QRegExp("\\[(.*)\\]\\s?\\[(.*)\\]");
    this->_regex[MarkdownDefine::REFERENCE_LINK].setMinimal(true);
    this->_regex[MarkdownDefine::EMPHASIS] = QRegExp("\\*[^\\*\\s\\t].+[^\\*\\s\\t]\\*|_[^_\\s\\t]+_");
    this->_regex[MarkdownDefine::EMPHASIS].setMinimal(true);
    this->_regex[MarkdownDefine::STRONG] = QRegExp("\\*{2}[^\\*\\s\\t].+[^\\*\\s\\t]\\*{2}|_{2}[^_\\s\\t]+_{2}");
    this->_regex[MarkdownDefine::STRONG].setMinimal(true);
    this->_regex[MarkdownDefine::IMAGE] = QRegExp("!\\[(.*)\\]\\s?\\(([^\\s]+)(.*)\\)");
    this->_regex[MarkdownDefine::IMAGE].setMinimal(true);
    this->_regex[MarkdownDefine::INLINE_CODE] = QRegExp("`.*`");
    this->_regex[MarkdownDefine::INLINE_CODE].setMinimal(true);
}
