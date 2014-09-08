#include "ParseElementLinkAutomatic.h"

ParseElementLinkAutomatic::ParseElementLinkAutomatic() : ParseElementSpan(), ParseElementLink() {
}

ParseElementType ParseElementLinkAutomatic::type() const {
    return ParseElementType::TYPE_LINK_AUTOMATIC;
}

qint32 ParseElementLinkAutomatic::tryParse(const QString& text, qint32 offset) {
    qint32 index = offset;
    if (this->ParserOpenClose(text, index, this->_link, '<', '>')) {
        if (isLink() || isEmail()) {
            return index - offset;
        }
    }
    return 0;
}

QString ParseElementLinkAutomatic::generateOpenHtml() const {
    if (this->isLink()) {
        return this->generateOpenLinkHtml(this->_link, "") + this->_link + "</a>";
    }
    return this->generateOpenLinkHtml(this->htmlEscaped("mailto:" + this->_link), "") +
           this->htmlEscaped(this->_link) + "</a>";
}

bool ParseElementLinkAutomatic::isLink() const {
    if (this->_link.size() >= 7) {
        return this->_link.mid(0, 7) == "http://";
    }
    return false;
}

bool ParseElementLinkAutomatic::isEmail() const {
    enum EmailStatus {
        STATUS_TEXT1,
        STATUS_AT,
        STATUS_TEXT2,
        STATUS_DOT,
        STATUS_TEXT3,
    };
    EmailStatus status = STATUS_TEXT1;
    qint32 length = this->_link.length();
    for (qint32 i = 0; i < length; ++i) {
        QChar ch = this->_link[i];
        switch (status) {
        case STATUS_TEXT1:
            if (ch == '@') {
                status = STATUS_AT;
            } else if (ch.isSpace()) {
                return false;
            } else if (ch < 0) {
                return false;
            }
            break;
        case STATUS_AT:
            if (ch.isSpace()) {
                return false;
            } else if (ch > 0) {
                status = STATUS_TEXT2;
            } else {
                return false;
            }
            break;
        case STATUS_TEXT2:
            if (ch == '.') {
                status = STATUS_DOT;
            } else if (ch.isSpace()) {
                return false;
            } else if (ch < 0) {
                return false;
            }
            break;
        case STATUS_DOT:
            if (ch.isSpace()) {
                return false;
            } else if (ch > 0) {
                status = STATUS_TEXT3;
            } else {
                return false;
            }
            break;
        case STATUS_TEXT3:
            if (ch.isSpace()) {
                return false;
            } else if (ch < 0) {
                return false;
            }
            break;
        default:
            break;
        }
    }
    return status == STATUS_TEXT3;
}

QString ParseElementLinkAutomatic::htmlEscaped(const QString& text) const {
    QString amp;
    qint32 length = text.length();
    for (qint32 i = 0; i < length; ++i) {
        amp += QString("&#%1;").arg((qint32)text[i].toLatin1());
    }
    return amp;
}
