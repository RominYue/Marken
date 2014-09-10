#include "ParseElementLink.h"

ParseElementLink::ParseElementLink() {
}

bool ParseElementLink::parseOpenClose(const QString& text, int& index, QString& inner, QChar open, QChar close) {
    Status status = STATUS_BEGIN;
    int length = text.length();
    int offset = index;
    while (index < length) {
        QChar ch = text[index];
        switch (status) {
        case STATUS_BEGIN:
            if (ch == open) {
                status = STATUS_LEFT;
            } else {
                return false;
            }
            break;
        case STATUS_LEFT:
            if (ch == '\\') {
                status = STATUS_ESCAPE;
            } else if (ch == close) {
                ++index;
                inner = "";
                return true;
            } else {
                status = STATUS_TEXT;
            }
            break;
        case STATUS_TEXT:
            if (ch == '\\') {
                status = STATUS_ESCAPE;
            } else if (ch == close) {
                status = STATUS_RIGHT;
            } else {
                status = STATUS_TEXT;
            }
            break;
        case STATUS_ESCAPE:
            status = STATUS_TEXT;
            break;
        case STATUS_RIGHT:
        default:
            break;
        }
        ++index;
        if (status == STATUS_RIGHT) {
            inner = text.mid(offset + 1, index - offset - 2);
            return true;
        }
    }
    return false;
}

bool ParseElementLink::parseBrackets(const QString& text, int& index, QString& inner) {
    return parseOpenClose(text, index, inner, '[', ']');
}

bool ParseElementLink::parseParentheses(const QString& text, int& index, QString& inner) {
    return parseOpenClose(text, index, inner, '(', ')');
}

bool ParseElementLink::parseLink(const QString& text, int& index, QString& link) {
    int length = text.length();
    for (; index < length; ++index) {
        if (!text[index].isSpace()) {
            break;
        }
    }
    if (index < length) {
        int start = index;
        if (text[index] == '<') {
            for (++index; index < length; ++index) {
                if (text[index] == '>') {
                    if (index + 1 < length) {
                        if (!text[index + 1].isSpace()) {
                            return false;
                        }
                    }
                    ++index;
                    link = text.mid(start + 1, index - start - 2);
                    return true;
                }
            }
        } else {
            for (++index; index < length; ++index) {
                if (text[index].isSpace()) {
                    break;
                }
            }
            link = text.mid(start, index - start);
            return true;
        }
    } else {
        link = "";
        return true;
    }
    return false;
}

bool ParseElementLink::parseTitle(const QString& text, int& index, QString& title) {
    int length = text.length();
    title = text.mid(index, length - index).trimmed();
    if (title.length() > 0) {
        QChar first = title[0];
        QChar last = title[title.length() - 1];
        if ((first == '"' && last == '"') ||
            (first == '\'' && last == '\'') ||
            (first == '(' && last == ')')) {
            title = title.mid(1, title.length() - 2);
            return true;
        }
    } else {
        return true;
    }
    return false;
}

QString ParseElementLink::generateOpenLinkHtml(const QString& href, const QString& title) const {
    if (title.length() > 0) {
        return QString("<a href=\"") + href + QString("\" title=\"") + title + QString("\">");
    }
    return QString("<a href=\"") + href + QString("\">");
}
