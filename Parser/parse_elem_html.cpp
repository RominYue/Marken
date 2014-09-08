#include "parse_elem_html.h"
using namespace std;

ParseElementHtml::ParseElementHtml() {
}

const string& ParseElementHtml::tag() const {
    return this->_tag;
}

void ParseElementHtml::setTag(const string& val) {
    this->_tag = "";
    for (auto ch : val) {
        if (ch >= 'A' && ch <= 'Z') {
            this->_tag += (char)(ch - 'A' + 'a');
        } else {
            this->_tag += ch;
        }
    }
}

bool ParseElementHtml::findOpenTagOffset(const string &line, int &index) {
    Status status = STATUS_BEGIN;
    int lineLength = line.length();
    while (index < lineLength) {
        char ch = line[index];
        switch (status) {
        case STATUS_BEGIN:
            if (ch == '<') {
                status = STATUS_LT;
            } else {
                return false;
            }
            break;
        case STATUS_LT:
            if (isspace(ch)) {
                status = STATUS_LT;
            } else if (isalpha(ch)) {
                status = STATUS_TAG;
                return true;
            } else {
                return false;
            }
            break;
        default:
            return false;
        }
        ++index;
    }
    return false;
}

bool ParseElementHtml::findCloseTagOffset(const string &line, int &index) {
    Status status = STATUS_BEGIN;
    int lineLength = line.length();
    while (index < lineLength) {
        char ch = line[index];
        switch (status) {
        case STATUS_BEGIN:
            if (ch == '<') {
                status = STATUS_LT;
            } else {
                return false;
            }
            break;
        case STATUS_LT:
            if (isspace(ch)) {
                status = STATUS_LT;
            } else if (ch == '/') {
                status = STATUS_SLASH;
            } else {
                return false;
            }
            break;
        case STATUS_SLASH:
            if (isspace(ch)) {
                status = STATUS_SLASH;
            } else if (isalpha(ch)) {
                status = STATUS_TAG;
                return true;
            } else {
                return false;
            }
            break;
        default:
            return false;
        }
        ++index;
    }
    return false;
}

bool ParseElementHtml::matchToTagEnd(const string &line, int &index) {
    int length = line.length();
    int start = index, end = length;
    for (int i = index; i < length; ++i) {
        if (isspace(line[i]) || line[i] == '>' || line[i] == '/') {
            end = i;
            break;
        }
    }
    this->setTag(line.substr(start, end - start));
    return true;
}

bool ParseElementHtml::matchToGt(const string &line, int &index) {
    Status status = STATUS_TAG;
    int lineLength = line.length();
    int tagStart = index, tagEnd = index;
    bool first = true;
    while (index < lineLength) {
        char ch = line[index];
        switch (status) {
        case STATUS_TAG:
            if (isspace(ch)) {
                status = STATUS_SPACE_SUF;
                if (first) {
                    tagEnd = index;
                    first = false;
                    this->setTag(line.substr(tagStart, tagEnd - tagStart));
                }
            } else if (ch == '>') {
                status = STATUS_GT;
                if (first) {
                    tagEnd = index;
                    first = false;
                    this->setTag(line.substr(tagStart, tagEnd - tagStart));
                }
                ++index;
                return true;
            } else if (ch < 0) {
                return false;
            }
            break;
        case STATUS_SPACE_SUF:
            if (isspace(ch)) {
                status = STATUS_SPACE_SUF;
            } else if (ch == '>') {
                status = STATUS_GT;
                ++index;
                return true;
            } else if (ch == '"') {
                status = STATUS_STRING;
            } else {
                status = STATUS_ATTRIBUTE;
            }
            break;
        case STATUS_ATTRIBUTE:
            if (ch == '"') {
                status = STATUS_STRING;
            } else if (ch == '>') {
                status = STATUS_GT;
                ++index;
                return true;
            }
            break;
        case STATUS_STRING:
            if (ch == '"') {
                status = STATUS_ATTRIBUTE;
            } else if (ch == '\\') {
                status = STATUS_ESCAPE;
            }
            break;
        case STATUS_ESCAPE:
            status = STATUS_STRING;
            break;
        case STATUS_GT:
            break;
        default:
            return false;
        }
        ++index;
    }
    return false;
}

bool ParseElementHtml::matchToEnd(const string &line, int &index) {
    int lineLength = line.length();
    while (index < lineLength) {
        char ch = line[index];
        if (!isspace(ch)) {
            return false;
        }
    }
    return true;
}
