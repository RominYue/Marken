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
    this->_regex[MarkdownDefination::DEFAULT] = QRegExp("^.*$");
    this->_regex[MarkdownDefination::ATX_HEADER_1] = QRegExp("^#([^#].*|$)");
    this->_regex[MarkdownDefination::ATX_HEADER_2] = QRegExp("^#{2}([^#].*|$)");
    this->_regex[MarkdownDefination::ATX_HEADER_3] = QRegExp("^#{3}([^#].*|$)");
    this->_regex[MarkdownDefination::ATX_HEADER_4] = QRegExp("^#{4}([^#].*|$)");
    this->_regex[MarkdownDefination::ATX_HEADER_5] = QRegExp("^#{5}([^#].*|$)");
    this->_regex[MarkdownDefination::ATX_HEADER_6] = QRegExp("^#{6}([^#].*|$)");
    this->_regex[MarkdownDefination::SETEXT_HEADER_1] = QRegExp("^=+$");
    this->_regex[MarkdownDefination::SETEXT_HEADER_2] = QRegExp("^-+$");
    this->_regex[MarkdownDefination::HORIZONTAL] = QRegExp("^([\\*-_]\\W*){3,}$");
    this->_regex[MarkdownDefination::BLOCK_QUOTE] = QRegExp("^>");
    this->_regex[MarkdownDefination::UNORDERED_LIST] = QRegExp("^[\\*\\+-]");
    this->_regex[MarkdownDefination::ORDERED_LIST] = QRegExp("^\\d+\\.");
    this->_regex[MarkdownDefination::CODE_BLOCK] = QRegExp("^\\s{4}|^\\t");
    this->_regex[MarkdownDefination::INLINE_LINK] = QRegExp("\\[.*\\]\\(.*\\)");
    this->_regex[MarkdownDefination::INLINE_LINK].setMinimal(true);
    this->_regex[MarkdownDefination::REFERENCE_LINK] = QRegExp("\\[.*\\]\\[.*\\]");
    this->_regex[MarkdownDefination::REFERENCE_LINK].setMinimal(true);
    this->_regex[MarkdownDefination::LINK_LABEL] = QRegExp("^\\[.*\\]:.*$");
    this->_regex[MarkdownDefination::LINK_LABEL].setMinimal(true);
    this->_regex[MarkdownDefination::EMPHASIS] = QRegExp("\\*.+\\*|_.+_");
    this->_regex[MarkdownDefination::EMPHASIS].setMinimal(true);
    this->_regex[MarkdownDefination::STRONG] = QRegExp("\\*\\*.+\\*\\*|__.+__");
    this->_regex[MarkdownDefination::STRONG].setMinimal(true);
    this->_regex[MarkdownDefination::IMAGE] = QRegExp("!\\[.*\\]\\[.*\\]");
    this->_regex[MarkdownDefination::IMAGE].setMinimal(true);
    this->_regex[MarkdownDefination::INLINE_CODE] = QRegExp("`.*`");
    this->_regex[MarkdownDefination::INLINE_CODE].setMinimal(true);
}
