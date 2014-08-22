#include "Setting.h"
#include "MarkdownHighlighter.h"

MarkdownHighlighter::MarkdownHighlighter(QTextDocument *parent) :
    QSyntaxHighlighter(parent) {
}

void MarkdownHighlighter::highlightBlock(const QString &text) {
    ColorSchemeSetting& colorScheme = Setting::instance()->colorScheme;
    auto regex = this->_regex.regex();
    for (auto name : regex.keys()) {
        QRegExp val = regex.value(name);
        int index = val.indexIn(text);
        while (index >= 0) {
            int length = val.matchedLength();
            if (length == 0) {
                break;
            }
            if (index == 0 || text[index - 1] != '\\') {
                setFormat(index, length, colorScheme.format(MarkdownDefination::getString(name)));
            }
            if (length == text.size() && name != MarkdownDefination::DEFAULT) {
                return;
            }
            index = val.indexIn(text, index + length);
        }
    }
}
