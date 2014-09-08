#include "parse_elem_link.h"
using namespace std;

ParseElementLink::ParseElementLink() {
}

bool ParseElementLink::parseOpenClose(const string& text, int& index, string& inner, char open, char close) {
    Status status = STATUS_BEGIN;
    int length = text.length();
    int offset = index;
    while (index < length) {
        char ch = text[index];
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
            inner = text.substr(offset + 1, index - offset - 2);
            return true;
        }
    }
    return false;
}

bool ParseElementLink::parseBrackets(const string& text, int& index, string& inner) {
    return parseOpenClose(text, index, inner, '[', ']');
}

bool ParseElementLink::parseParentheses(const string& text, int& index, string& inner) {
    return parseOpenClose(text, index, inner, '(', ')');
}

string ParseElementLink::getCleanedLink(const string& link) const {
    int len = link.length();
    int start = 0;
    for (int i = 0; i < len; ++i) {
        if (!isspace(link[i])) {
            start = i;
            break;
        }
    }
    int end = len - 1;
    for (int i = len - 1; i >= 0; --i) {
        if (!isspace(link[i])) {
            end = i;
            break;
        }
    }
    if (start > end) {
        return "";
    }
    if (link[start] == '<' && link[end] == '>') {
        return link.substr(start + 1, end - start - 1);
    }
    return link.substr(start, end - start + 1);
}

string ParseElementLink::getCleanedTitle(const string& title) const {
    int len = title.length();
    int start = 0;
    for (int i = 0; i < len; ++i) {
        if (!isspace(title[i])) {
            start = i;
            break;
        }
    }
    int end = len - 1;
    for (int i = len - 1; i >= 0; --i) {
        if (!isspace(title[i])) {
            end = i;
            break;
        }
    }
    if (start > end) {
        return "";
    }
    if (title[start] == '"' || title[start] == '\'' || (title[start] == '(' && title[end] == ')')) {
        return title.substr(start + 1, end - start - 1);
    }
    return title.substr(start, end - start + 1);
}

string ParseElementLink::getCleanedLabel(const string& label) const {
    int len = label.length();
    int start = 0;
    for (int i = 0; i < len; ++i) {
        if (!isspace(label[i])) {
            start = i;
            break;
        }
    }
    int end = len - 1;
    for (int i = len - 1; i >= 0; --i) {
        if (!isspace(label[i])) {
            end = i;
            break;
        }
    }
    if (start > end) {
        return "";
    }
    string cleaned;
    for (int i = start; i <= end; ++i) {
        if (label[i] >= 'A' && label[i] <= 'Z') {
            cleaned += label[i] - 'A' + 'a';
        } else {
            cleaned += label[i];
        }
    }
    return cleaned;
}

string ParseElementLink::generateOpenLinkHtml(const string& href, const string& title) const {
    if (title.length() > 0) {
        return string("<a href=\"") + href + string("\" title=\"") + title + string("\">");
    }
    return string("<a href=\"") + href + string("\">");
}
