#include "ParseElementLink.h"

ParseElementLink::ParseElementLink() {
}

bool ParseElementLink::ParserOpenClose(const QString& text, qint32& index, QString& inner, QChar open, QChar close) {
    Status status = STATUS_BEGIN;
    qint32 length = text.length();
    qint32 offset = index;
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

bool ParseElementLink::ParserBrackets(const QString& text, qint32& index, QString& inner) {
    return ParserOpenClose(text, index, inner, '[', ']');
}

bool ParseElementLink::ParserParentheses(const QString& text, qint32& index, QString& inner) {
    return ParserOpenClose(text, index, inner, '(', ')');
}

QString ParseElementLink::getCleanedLink(const QString& link) const {
    qint32 len = link.length();
    qint32 start = 0;
    for (qint32 i = 0; i < len; ++i) {
        if (!link[i].isSpace()) {
            start = i;
            break;
        }
    }
    qint32 end = len - 1;
    for (qint32 i = len - 1; i >= 0; --i) {
        if (!link[i].isSpace()) {
            end = i;
            break;
        }
    }
    if (start > end) {
        return "";
    }
    if (link[start] == '<' && link[end] == '>') {
        return link.mid(start + 1, end - start - 1);
    }
    return link.mid(start, end - start + 1);
}

QString ParseElementLink::getCleanedTitle(const QString& title) const {
    qint32 len = title.length();
    qint32 start = 0;
    for (qint32 i = 0; i < len; ++i) {
        if (!title[i].isSpace()) {
            start = i;
            break;
        }
    }
    qint32 end = len - 1;
    for (qint32 i = len - 1; i >= 0; --i) {
        if (!title[i].isSpace()) {
            end = i;
            break;
        }
    }
    if (start > end) {
        return "";
    }
    if (title[start] == '"' || title[start] == '\'' || (title[start] == '(' && title[end] == ')')) {
        return title.mid(start + 1, end - start - 1);
    }
    return title.mid(start, end - start + 1);
}

QString ParseElementLink::getCleanedLabel(const QString& label) const {
    qint32 len = label.length();
    qint32 start = 0;
    for (qint32 i = 0; i < len; ++i) {
        if (!label[i].isSpace()) {
            start = i;
            break;
        }
    }
    qint32 end = len - 1;
    for (qint32 i = len - 1; i >= 0; --i) {
        if (!label[i].isSpace()) {
            end = i;
            break;
        }
    }
    if (start > end) {
        return "";
    }
    QString cleaned;
    for (qint32 i = start; i <= end; ++i) {
        if (label[i] >= 'A' && label[i] <= 'Z') {
            cleaned += label[i].toLatin1() - 'A' + 'a';
        } else {
            cleaned += label[i];
        }
    }
    return cleaned;
}

QString ParseElementLink::generateOpenLinkHtml(const QString& href, const QString& title) const {
    if (title.length() > 0) {
        return QString("<a href=\"") + href + QString("\" title=\"") + title + QString("\">");
    }
    return QString("<a href=\"") + href + QString("\">");
}
