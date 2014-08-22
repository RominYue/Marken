#include "MarkdownCompiler.h"

MarkdownCompiler::MarkdownCompiler() {
}

void MarkdownCompiler::analysis(const QStringList &list) {
    this->_types.clear();
    for (int i = 0; i < list.size(); ++i) {
        if (this->_regex.empty().indexIn(list[i]) == 0) {
            this->_types.push_back(LINE_EMPTY);
        } if (this->_regex.regex(MarkdownDefination::ATX_HEADER_1).indexIn(list[i]) == 0) {
            this->_types.push_back(LINE_ATX_HEADER_1);
        } else if (this->_regex.regex(MarkdownDefination::ATX_HEADER_2).indexIn(list[i]) == 0) {
            this->_types.push_back(LINE_ATX_HEADER_2);
        } else if (this->_regex.regex(MarkdownDefination::ATX_HEADER_3).indexIn(list[i]) == 0) {
            this->_types.push_back(LINE_ATX_HEADER_3);
        } else if (this->_regex.regex(MarkdownDefination::ATX_HEADER_4).indexIn(list[i]) == 0) {
            this->_types.push_back(LINE_ATX_HEADER_4);
        } else if (this->_regex.regex(MarkdownDefination::ATX_HEADER_5).indexIn(list[i]) == 0) {
            this->_types.push_back(LINE_ATX_HEADER_5);
        } else if (this->_regex.regex(MarkdownDefination::ATX_HEADER_6).indexIn(list[i]) == 0) {
            this->_types.push_back(LINE_ATX_HEADER_6);
        } else if (this->_regex.regex(MarkdownDefination::SETEXT_HEADER_1).indexIn(list[i]) == 0) {
            if (i > 0) {
                this->_types[i - 1] = LINE_SETEXT_HEADER_1;
            }
            this->_types.push_back(LINE_HORIZONTAL);
        } else if (this->_regex.regex(MarkdownDefination::SETEXT_HEADER_2).indexIn(list[i]) == 0) {
            if (i > 0) {
                this->_types[i -  1] = LINE_SETEXT_HEADER_2;
            }
            this->_types.push_back(LINE_HORIZONTAL);
        } else if (this->_regex.regex(MarkdownDefination::HORIZONTAL).indexIn(list[i]) == 0) {
            this->_types.push_back(LINE_HORIZONTAL);
        } else {
            this->_types.push_back(LINE_DEFAULT);
        }
    }
}

QString MarkdownCompiler::parseToHTML(const QStringList &list) {
    QString html;
    this->analysis(list);
    for (int i = 0; i < list.size(); ++i) {
        switch (this->_types[i]) {
        case LINE_DEFAULT:
            html += translate(list[i]) + "\n";
            break;
        case LINE_EMPTY:
            break;
        case LINE_ATX_HEADER_1:
            html += "<h1>" + cleanHeader(list[i]) + "</h1>\n<hr>\n";
            break;
        case LINE_ATX_HEADER_2:
            html += "<h2>" + cleanHeader(list[i]) + "</h2>\n<hr>\n";
            break;
        case LINE_ATX_HEADER_3:
            html += "<h3>" + cleanHeader(list[i]) + "</h3>\n<hr>\n";
            break;
        case LINE_ATX_HEADER_4:
            html += "<h4>" + cleanHeader(list[i]) + "</h4>\n";
            break;
        case LINE_ATX_HEADER_5:
            html += "<h5>" + cleanHeader(list[i]) + "</h5>\n";
            break;
        case LINE_ATX_HEADER_6:
            html += "<h6>" + cleanHeader(list[i]) + "</h6>\n";
            break;
        case LINE_SETEXT_HEADER_1:
            html += "<h1>" + cleanHeader(list[i]) + "</h1>\n";
            break;
        case LINE_SETEXT_HEADER_2:
            html += "<h2>" + cleanHeader(list[i]) + "</h2>\n";
            break;
        case LINE_BLOCK_QUOTE:
            break;
        case LINE_UNORDERED_LIST:
            break;
        case LINE_ORDERED_LIST:
            break;
        case LINE_CODE_BLOCK:
            break;
        case LINE_HORIZONTAL:
            html += "<hr>\n";
            break;
        case LINE_LINK_LABEL:
            break;
        }
    }
    return html;
}

QString MarkdownCompiler::cleanHeader(const QString& header) const {
    int start = 0;
    int end = header.size() - 1;
    for (; start < header.size(); ++start) {
        if (header[start] != '#' && header[start] != ' ' && header[start] != '\t') {
            break;
        }
    }
    for (; end >= 0; --end) {
        if (header[end] != '#' && header[end] != ' ' && header[end] != '\t') {
            ++end;
            break;
        }
    }
    if (start < end) {
        return header.mid(start, end - start);
    }
    return "";
}

int MarkdownCompiler::findNext(const QString &str, char ch, int index) const {
    bool escape = false;
    for (int i = index; i < str.size(); ++i) {
        if (str[i] == ch) {
            if (escape) {
                escape = false;
            } else {
                return i;
            }
        } else if (str[i] == '\\') {
            escape ^= true;
        } else {
            escape = false;
        }
    }
    return -1;
}

QString MarkdownCompiler::getLink(const QString &str) const {
    int index = findNext(str, ']');
    QString name = str.mid(1, index - 1);
    index = findNext(str, '(', index);
    int start = index + 1;
    int temp1 = findNext(str, ' ', index);
    int temp2 = findNext(str, ')', index);
    if (temp1 != -1 && temp1 < temp2) {
        QString href = str.mid(start, temp1 - start);
        index = findNext(str, ')', index);
        QString title = cleanHeader(str.mid(temp1, temp2 - temp1));
        return "<a href=\"" + href + "\" title=" + title + ">" + name + "</a>";
    }
    index = findNext(str, ')', index);
    QString href = str.mid(start, temp2 - start);
    return "<a href=\"" + href + "\">" + name + "</a>";
}

QString MarkdownCompiler::translate(const QString& str) const {
    QString html;
    for (int i = 0; i < str.size(); ++i) {
        if (str[i] == '<') {
            html += "&lt;";
        } else if (str[i] == '>') {
            html += "&gt;";
        } else if (str[i] == '&') {
            html += "&amp;";
        } else {
            html += str[i];
        }
    }
    int index = 0;
    index = this->_regex.regex(MarkdownDefination::STRONG).indexIn(html);
    while (index >= 0) {
        int length = this->_regex.regex(MarkdownDefination::STRONG).matchedLength();
        html.replace(index, length, "<strong>" + html.mid(index + 2, length - 4) + "</strong>");
        index = this->_regex.regex(MarkdownDefination::STRONG).indexIn(html, index + length);
    }
    index = this->_regex.regex(MarkdownDefination::EMPHASIS).indexIn(html);
    while (index >= 0) {
        int length = this->_regex.regex(MarkdownDefination::EMPHASIS).matchedLength();
        html.replace(index, length, "<em>" + html.mid(index + 1, length - 2) + "</em>");
        index = this->_regex.regex(MarkdownDefination::EMPHASIS).indexIn(html, index + length);
    }
    index = this->_regex.regex(MarkdownDefination::INLINE_LINK).indexIn(html);
    while (index >= 0) {
        int length = this->_regex.regex(MarkdownDefination::INLINE_LINK).matchedLength();
        html.replace(index, length, getLink(html.mid(index, length)));
        index = this->_regex.regex(MarkdownDefination::INLINE_LINK).indexIn(html, index + length);
    }
    return html;
}
