#include <QStringList>
#include "MarkdownParser.h"

MarkdownParser::MarkdownParser() {
}

QString MarkdownParser::generateHtml(MarkdownEditor *editor) {
    QString html;
    QStringList list;
    QTextBlock block = editor->document()->firstBlock();
    while (block.isValid()) {
        QString temp;
        MarkdownBlockData* data = dynamic_cast<MarkdownBlockData*>(block.userData());
        switch (data->type()) {
        case MarkdownBlockData::LINE_ATX_HEADER_1:
            list << "<h1>" + translate(removeTitleHash(block.text())) + "</h1><hr>";
            break;
        case MarkdownBlockData::LINE_ATX_HEADER_2:
            list << "<h2>" + translate(removeTitleHash(block.text())) + "</h2><hr>";
            break;
        case MarkdownBlockData::LINE_ATX_HEADER_3:
            list << "<h3>" + translate(removeTitleHash(block.text())) + "</h3><hr>";
            break;
        case MarkdownBlockData::LINE_ATX_HEADER_4:
            list << "<h4>" + translate(removeTitleHash(block.text())) + "</h4>";
            break;
        case MarkdownBlockData::LINE_ATX_HEADER_5:
            list << "<h5>" + translate(removeTitleHash(block.text())) + "</h5>";
            break;
        case MarkdownBlockData::LINE_ATX_HEADER_6:
            list << "<h6>" + translate(removeTitleHash(block.text())) + "</h6>";
            break;
        case MarkdownBlockData::LINE_BLOCK_HTML:
        case MarkdownBlockData::LINE_BLOCK_HTML_END:
            list << block.text();
            break;
        case MarkdownBlockData::LINE_CODE_BLOCK:
            if (this->prevFirstType(block) != MarkdownBlockData::LINE_CODE_BLOCK) {
                temp += "<pre><code>";
            }
            temp += removeCodeIndent(translate(block.text())) + "<br>";
            if (this->nextFirstType(block) != MarkdownBlockData::LINE_CODE_BLOCK) {
                temp += "</pre></code>";
            }
            list << temp;
            break;
        case MarkdownBlockData::LINE_DEFAULT:
            if (this->prevFirstType(block) != MarkdownBlockData::LINE_DEFAULT) {
                temp += "<p>";
            }
            temp += translateSpan(block.text());
            if (this->nextFirstType(block) != MarkdownBlockData::LINE_DEFAULT) {
                temp += "</p>";
            }
            list << temp;
            break;
        case MarkdownBlockData::LINE_EMPTY:
            list << "";
            break;
        case MarkdownBlockData::LINE_HORIZONTAL:
            list << "<hr>";
            break;
        case MarkdownBlockData::LINE_LINK_LABEL:
            list << "";
            break;
        case MarkdownBlockData::LINE_NESTED_BLOCK:
            block = this->parseNestedBlock(block, list).previous();
            break;
        case MarkdownBlockData::LINE_SETEXT_HEADER_1:
            if (this->prevFirstType(block) == MarkdownBlockData::LINE_DEFAULT) {
                list.last() = "<h1>" + translate(removeTitleHash(block.text())) + "</h1>";
            }
            list << "<hr>";
            break;
        case MarkdownBlockData::LINE_SETEXT_HEADER_2:
            if (this->prevFirstType(block) == MarkdownBlockData::LINE_DEFAULT) {
                list.last() = "<h2>" + translate(removeTitleHash(block.text())) + "</h2>";
            }
            list << "<hr>";
            break;
        default:
            list << "";
            break;
        }
        block = block.next();
    }
    for (int i = 0; i < list.size(); ++i) {
        html += list[i] + "\n";
    }
    return html;
}

MarkdownBlockData::LineType MarkdownParser::prevFirstType(QTextBlock& block) const {
    if (block.previous().isValid()) {
        return dynamic_cast<MarkdownBlockData*>(block.previous().userData())->type();
    }
    return MarkdownBlockData::LINE_INVALID;
}

MarkdownBlockData::LineType MarkdownParser::nextFirstType(QTextBlock& block) const {
    if (block.next().isValid()) {
        return dynamic_cast<MarkdownBlockData*>(block.next().userData())->type();
    }
    return MarkdownBlockData::LINE_INVALID;
}

QString MarkdownParser::removeCodeIndent(const QString &str) {
    if (str[0] == '\t') {
        return str.right(str.length() - 1);
    }
    return str.right(str.length() - 4);
}

QString MarkdownParser::translate(const QString &str) {
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

QString MarkdownParser::removeTitleHash(const QString &str) {
    for (int i = 0 ; i < str.length(); ++i) {
        if (str[i] != '#' && str[i] != ' ') {
            for (int j = str.length() - 1; j >= i; --j) {
                if (str[j] != '#' && str[j] != ' ') {
                    if (str[j] == '\\') {
                        ++j;
                    }
                    return str.mid(i, j + 1 - i);
                }
            }
        }
    }
    return "";
}

QString MarkdownParser::translateSpan(const QString &str) {
    QString translated;
    QString temp;
    int length;
    bool trans = false;
    for (int i = 0; i < str.length(); ++i) {
        length = -1;
        if (str[i] == '\\') {
            trans ^= true;
        } else {
            if (!trans) {
                if (str[i] == '!') {
                    temp = parseImage(str, i, length);
                } else if (str[i] == '[') {
                    temp = parseLink(str, i, length);
                } else if (str[i] == '`') {
                    temp = parseCode(str, i, length);
                } else if (str[i] == '<') {
                    temp = parseHtml(str, i, length);
                } else if (str[i] == '*' || str[i] == '_') {
                    temp = parseEmphasis(str, i, length);
                } else if (str[i] == '&') {
                    temp = parseTransChar(str, i, length);
                }
            }
            trans = false;
        }
        if (length > 0) {
            translated += temp;
            i += length - 1;
            continue;
        }
        if (!trans) {
            if (str[i] == '<') {
                translated += "&lt;";
            } else if (str[i] == '>') {
                translated += "&gt;";
            } else if (str[i] == '&') {
                translated += "&amp;";
            } else {
                translated += str[i];
            }
        }
    }
    return translated;
}

QString MarkdownParser::parseImage(const QString &str, int offset, int &length) {
    QRegExp image("!\\[(.*)\\]\\s?\\(([^\\s]+)(.*)\\)");
    image.setMinimal(true);
    int index = image.indexIn(str, offset);
    if (index == offset) {
        length = image.matchedLength();
        auto list = image.capturedTexts();
        if (list.size() == 3) {
            return "<img src=\"" + list[1] + "\" alt=\"" + list[2] + "\">";
        } else if (list.size() == 4) {
            return "<img src=\"" + list[1] + "\" alt=\"" + list[2] + "\" title=\"" + list[3] + "\">";
        }
    }
    return "";
}

QString MarkdownParser::parseLink(const QString &str, int offset, int &length) {
    QRegExp link("\\[(.*)\\]\\s?\\(([^\\s]+)(.*)\\)");
    link.setMinimal(true);
    int index = link.indexIn(str, offset);
    if (index == offset) {
        length = link.matchedLength();
        auto list = link.capturedTexts();
        if (list.size() == 3) {
            return "<a href=\"" + list[2] + "\">" + list[1] + "</a>";
        } else if (list.size() == 4) {
            return "<a href=\"" + list[2] + "\" title=\"" + list[3] + "\">" + list[1] + "</a>";
        }
    }
    return "";
}

QString MarkdownParser::parseCode(const QString &str, int offset, int &length) {
    int num = 0;
    for (int i = offset; i < str.length(); ++i) {
        if (str[i] == '`') {
            ++num;
        } else {
            break;
        }
    }
    QRegExp code(QString("`{%1}.*`{%1}").arg(num));
    code.setMinimal(true);
    int index = code.indexIn(str, offset);
    if (index == offset) {
        length = code.matchedLength();
        return "<code>" + str.mid(offset + num, length - num * 2) + "</code>";
    }
    return "";
}

QString MarkdownParser::parseHtml(const QString &str, int offset, int &length) {
    QRegExp html("</?(.*)>");
    html.setMinimal(true);
    int index = html.indexIn(str, offset);
    if (index == offset) {
        QString tag = html.capturedTexts()[1];
        for (auto spanTag : {"h1", "h2", "h3", "h4", "h5", "h6", "hr", "a", "abbr", "b", "big", "br", "cite",
                             "code", "em", "i", "img", "small", "span", "strong", "sub", "sup", "del"}) {
            if (spanTag == tag) {
                return "";
            }
        }
        length = html.matchedLength();
        return str.mid(offset, offset + length);
    }
    return "";
}

QString MarkdownParser::parseEmphasis(const QString &str, int offset, int &length) {
    QRegExp strong("[\\*_]{2}([^\\s].*[^\\s]|[^\\s])[\\*_]{2}");
    strong.setMinimal(true);
    int index = strong.indexIn(str, offset);
    if (index == offset) {
        length = strong.matchedLength();
        return "<strong>" + strong.capturedTexts()[1] + "</strong>";
    }
    QRegExp emphasis("[\\*_]([^\\s].*[^\\s]|[^\\s])[\\*_]");
    emphasis.setMinimal(true);
    index = strong.indexIn(str, offset);
    if (index == offset) {
        length = emphasis.matchedLength();
        return "<em>" + emphasis.capturedTexts()[1] + "</em>";
    }
    return "";
}

QString MarkdownParser::parseTransChar(const QString &str, int offset, int &length) {
    QRegExp hChar("&(.+);");
    hChar.setMinimal(true);
    int index = hChar.indexIn(str, offset);
    if (index == offset) {
        QString tag = hChar.capturedTexts()[1];
        bool flag = true;
        for (auto hTag : {"nbsp", "lt", "gt", "amp", "cent", "pound", "yen", "euro", "copy", "reg"}) {
            if (tag == hTag) {
                flag = false;
                break;
            }
        }
        if (flag) {
            length = hChar.matchedLength();
            return str.mid(offset, length);
        }
    }
    QRegExp hNum("&#\\d+;");
    hNum.setMinimal(true);
    index = hChar.indexIn(str, offset);
    if (index == offset) {
        length = hNum.matchedLength();
        return str.mid(offset, length);
    }
    return "";
}

QTextBlock MarkdownParser::parseNestedBlock(QTextBlock block, QStringList& list) {
    enum State {
        QUOTE,
        UNORDERED,
        ORDERED,
    };
    QVector<State> prevState;
    return block;
}
