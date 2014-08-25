#include <QMap>
#include <QStringList>
#include "MarkdownParser.h"

MarkdownParser::MarkdownParser() {
}

QString MarkdownParser::generateHtml(QTextDocument *document) {
    QStringList list;
    this->findLinkLabels(document);
    QTextBlock block = document->firstBlock();
    while (block.isValid()) {
        QString html;
        QString text = block.text();
        MarkdownBlockData* data = dynamic_cast<MarkdownBlockData*>(block.userData());
        for (int i = 0; i < data->types()->size(); ++i) {
            int indent = data->indent(i);
            switch (data->type(i)) {
            case MarkdownBlockData::LINE_ATX_HEADER_1:
                html += "<h1>" + translate(removeTitleHash(text).mid(indent)) + "</h1><hr/>";
                break;
            case MarkdownBlockData::LINE_ATX_HEADER_2:
                html += "<h2>" + translate(removeTitleHash(text).mid(indent)) + "</h2><hr/>";
                break;
            case MarkdownBlockData::LINE_ATX_HEADER_3:
                html += "<h3>" + translate(removeTitleHash(text).mid(indent)) + "</h3><hr/>";
                break;
            case MarkdownBlockData::LINE_ATX_HEADER_4:
                html += "<h4>" + translate(removeTitleHash(text).mid(indent)) + "</h4>";
                break;
            case MarkdownBlockData::LINE_ATX_HEADER_5:
                html += "<h5>" + translate(removeTitleHash(text).mid(indent)) + "</h5>";
                break;
            case MarkdownBlockData::LINE_ATX_HEADER_6:
                html += "<h6>" + translate(removeTitleHash(text).mid(indent)) + "</h6>";
                break;
            case MarkdownBlockData::LINE_BLOCK_HTML:
            case MarkdownBlockData::LINE_BLOCK_HTML_END:
                html += text;
                break;
            case MarkdownBlockData::LINE_CODE_BLOCK:
                if (this->prevType(block, i) != MarkdownBlockData::LINE_CODE_BLOCK) {
                    html += "<pre><code>";
                }
                html += removeCodeIndent(translate(text.mid(indent))) + "<br/>";
                break;
            case MarkdownBlockData::LINE_DEFAULT:
                if (this->prevType(block, i) != MarkdownBlockData::LINE_DEFAULT) {
                    html += "<p>";
                }
                html += translateSpan(text.mid(indent));
                break;
            case MarkdownBlockData::LINE_EMPTY:
                html += "";
                break;
            case MarkdownBlockData::LINE_HORIZONTAL:
                html += "<hr/>";
                break;
            case MarkdownBlockData::LINE_LINK_LABEL:
            case MarkdownBlockData::LINE_LINK_LABEL_DESC:
                html += "";
                break;
            case MarkdownBlockData::LINE_SETEXT_HEADER_1:
                html += "<hr/>";
                break;
            case MarkdownBlockData::LINE_SETEXT_HEADER_2:
                html += "<hr/>";
                break;
            case MarkdownBlockData::LINE_BLOCK_QUOTE:
                if (this->prevType(block, i) != MarkdownBlockData::LINE_BLOCK_QUOTE) {
                    html += "<blockquote>";
                }
                break;
            case MarkdownBlockData::LINE_UNORDERED_LIST:
                if (this->prevType(block, i) != MarkdownBlockData::LINE_UNORDERED_LIST) {
                    html += "<ul>";
                }
                if (indent < text.length()) {
                    if (text.at(indent) == '*' || text.at(indent) == '+' || text.at(indent) == '-') {
                        html += "<li>" + translateSpan(text.mid(indent + 2));
                    }
                }
                break;
            case MarkdownBlockData::LINE_ORDERED_LIST:
                if (this->prevType(block, i) != MarkdownBlockData::LINE_ORDERED_LIST) {
                    html += "<ol>";
                }
                if (indent < text.length()) {
                    if (text.at(indent) >= '0' && text.at(indent) <= '9') {
                        html += "<li>" + translateSpan(text.mid(indent + 2));
                    }
                }
                break;
            default:
                html += text.mid(indent);
                break;
            }
        }
        for (int i = data->types()->size() - 1; i >= 0; --i) {
            int indent = data->indent(i);
            switch (data->type(i)) {
            case MarkdownBlockData::LINE_CODE_BLOCK:
                if (this->nextType(block, i) != MarkdownBlockData::LINE_CODE_BLOCK) {
                    html += "</code></pre>";
                }
                break;
            case MarkdownBlockData::LINE_DEFAULT:
                if (this->nextType(block, i) != MarkdownBlockData::LINE_DEFAULT) {
                    html += "</p>";
                }
                break;
            case MarkdownBlockData::LINE_BLOCK_QUOTE:
                if (this->nextType(block, i) != MarkdownBlockData::LINE_BLOCK_QUOTE) {
                    html += "</blockquote>";
                }
                break;
            case MarkdownBlockData::LINE_UNORDERED_LIST:
                if (indent < text.length()) {
                    if (text.at(indent) == '*' || text.at(indent) == '+' || text.at(indent) == '-') {
                        html += "</li>";
                    }
                }
                if (this->nextType(block, i) != MarkdownBlockData::LINE_UNORDERED_LIST) {
                    html += "</ul>";
                }
                break;
            case MarkdownBlockData::LINE_ORDERED_LIST:
                if (indent < text.length()) {
                    if (text.at(indent).isDigit()) {
                        html += "</li>";
                    }
                }
                if (this->nextType(block, i) != MarkdownBlockData::LINE_ORDERED_LIST) {
                    html += "</ol>";
                }
                break;
            default:
                break;
            }
        }
        list << html;
        block = block.next();
    }
    QString html = "";
    for (auto str : list) {
        html += str + "\n";
    }
    return html;
}

MarkdownBlockData::LineType MarkdownParser::prevType(QTextBlock& block, int index) const {
    if (block.previous().isValid()) {
        return dynamic_cast<MarkdownBlockData*>(block.previous().userData())->type(index);
    }
    return MarkdownBlockData::LINE_INVALID;
}

MarkdownBlockData::LineType MarkdownParser::nextType(QTextBlock& block, int index) const {
    if (block.next().isValid()) {
        MarkdownBlockData* data = dynamic_cast<MarkdownBlockData*>(block.next().userData());
        if (data != nullptr) {
            return data->type(index);
        }
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

QString MarkdownParser::removeSpaces(const QString &str) {
    for (int i = 0 ; i < str.length(); ++i) {
        if (str[i] != ' ' && str[i] != '\t') {
            for (int j = str.length() - 1; j >= i; --j) {
                if (str[j] != ' ' && str[i] != '\t') {
                    return str.mid(i, j + 1 - i);
                }
            }
        }
    }
    return "";
}

QString MarkdownParser::removeTitleHash(const QString &str) {
    for (int i = 0 ; i < str.length(); ++i) {
        if (str[i] != '#' && str[i] != ' ' && str[i] != '\t') {
            for (int j = str.length() - 1; j >= i; --j) {
                if (str[j] != '#' && str[j] != ' ' && str[i] != '\t') {
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
    QRegExp inlineLink("\\[(.*)\\]\\s?\\(([^\\s]+)(.*)\\)");
    inlineLink.setMinimal(true);
    int index = inlineLink.indexIn(str, offset);
    if (index == offset) {
        length = inlineLink.matchedLength();
        auto list = inlineLink.capturedTexts();
        if (list[3].isEmpty()) {
            return "<a href=\"" + list[2] + "\">" + list[1] + "</a>";
        } else {
            return "<a href=\"" + list[2] + "\" title=\"" + list[3] + "\">" + list[1] + "</a>";
        }
    }
    QRegExp referenceLink("\\[(.*)\\]\\s?\\[(.*)\\]");
    referenceLink.setMinimal(true);
    index = referenceLink.indexIn(str, offset);
    if (index == offset) {
        length = referenceLink.matchedLength();
        auto list = referenceLink.capturedTexts();
        QString key = list[2].toLower();
        if (key.isEmpty()) {
            key = list[1].toLower();
        }
        if (!key.isEmpty()) {
            if (this->_titles.find(key) == this->_titles.end()) {
                return "<a href=\"" + this->_links[key] + "\">" + list[1] + "</a>";
            } else {
                return "<a href=\"" + this->_links[key] + "\" title=\"" + this->_titles[key] + "\">" + list[1] + "</a>";
            }
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
    QRegExp strong("\\*{2}([^\\*\\s\\t].+[^\\*\\s\\t])\\*{2}|_{2}([^_\\s\\t]+)_{2}");
    strong.setMinimal(true);
    int index = strong.indexIn(str, offset);
    if (index == offset) {
        length = strong.matchedLength();
        return "<strong>" + strong.capturedTexts()[1] + "</strong>";
    }
    QRegExp emphasis("\\*([^\\*\\s\\t].+[^\\*\\s\\t])\\*|_([^_\\s\\t]+)_");
    emphasis.setMinimal(true);
    index = emphasis.indexIn(str, offset);
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

void MarkdownParser::findLinkLabels(QTextDocument *document) {
    this->_links.clear();
    this->_titles.clear();
    QRegExp linkLabel("\\[(.*)\\]:[\\s\\t]*([^\\s\\t]+)[\\s\\t]*(.*)$");
    linkLabel.setMinimal(true);
    QTextBlock block = document->firstBlock();
    QString lastLink;
    while (block.isValid()) {
        QString text = block.text();
        MarkdownBlockData* data = dynamic_cast<MarkdownBlockData*>(block.userData());
        for (int i = 0; i < data->types()->size(); ++i) {
            if (data[i].type(i) == MarkdownBlockData::LINE_LINK_LABEL) {
                linkLabel.indexIn(text, data->indent(i));
                if (linkLabel.capturedTexts().at(1).isEmpty()) {
                    break;
                }
                lastLink = linkLabel.capturedTexts().at(1).toLower();
                this->_links[lastLink] = linkLabel.capturedTexts().at(2);
                if (!linkLabel.capturedTexts().at(3).isEmpty()) {
                    this->_titles[lastLink] = linkLabel.capturedTexts().at(3);
                }
                break;
            }
            if (data[i].type(i) == MarkdownBlockData::LINE_LINK_LABEL_DESC) {
                if (!lastLink.isEmpty()) {
                    this->_titles[lastLink] = this->removeSpaces(text.mid(data->indent(i)));
                    lastLink = "";
                }
            }
        }
        block = block.next();
    }
}
