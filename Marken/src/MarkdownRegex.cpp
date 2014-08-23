#include "MarkdownRegex.h"

MarkdownRegex::MarkdownRegex() {
    this->initRegex();
}

const QMap<MarkdownDefination::SyntaxType, QRegExp>& MarkdownRegex::regex() const {
    return this->_regex;
}

const QRegExp& MarkdownRegex::regex(MarkdownDefination::SyntaxType name) const {
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
    this->_regex[MarkdownDefination::INLINE_LINK] = QRegExp("\\[(.*)\\]\\s?\\(([^\\s]+)(.*)\\)");
    this->_regex[MarkdownDefination::INLINE_LINK].setMinimal(true);
    this->_regex[MarkdownDefination::REFERENCE_LINK] = QRegExp("!\\[(.*)\\]\\s?\\[([^\\s]+)(.*)\\]");
    this->_regex[MarkdownDefination::REFERENCE_LINK].setMinimal(true);
    this->_regex[MarkdownDefination::LINK_LABEL] = QRegExp("^\\[.*\\]:.*$");
    this->_regex[MarkdownDefination::LINK_LABEL].setMinimal(true);
    this->_regex[MarkdownDefination::EMPHASIS] = QRegExp("\\*.+\\*|_.+_");
    this->_regex[MarkdownDefination::EMPHASIS].setMinimal(true);
    this->_regex[MarkdownDefination::STRONG] = QRegExp("\\*\\*.+\\*\\*|__.+__");
    this->_regex[MarkdownDefination::STRONG].setMinimal(true);
    this->_regex[MarkdownDefination::IMAGE] = QRegExp("!\\[(.*)\\]\\s?\\(([^\\s]+)(.*)\\)");
    this->_regex[MarkdownDefination::IMAGE].setMinimal(true);
    this->_regex[MarkdownDefination::INLINE_CODE] = QRegExp("`.*`");
    this->_regex[MarkdownDefination::INLINE_CODE].setMinimal(true);
}
