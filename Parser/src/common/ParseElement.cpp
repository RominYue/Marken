#include "ParseLineData.h"
#include "ParseElement.h"

ParseElement::ParseElement() {
    offset = 0;
    offset = 0;
    length = 0;
    parent = nullptr;
}

ParseElementType ParseElement::type() const {
    return ParseElementType::TYPE_INVALID;
}

bool ParseElement::isBlockElement() const {
    return false;
}

QString ParseElement::innerText() const {
    return "";
}

qint32 ParseElement::innerOffset() const {
    return 0;
}

void ParseElement::remove() {
}

QString ParseElement::htmlEscaped(const QString& text) const {
    QString html;
    qint32 tab = 0;
    for (qint32 i = 0; i < text.length(); ++i) {
        if (text[i].toLatin1() == '\t') {
            if (tab == 0) {
                html += "    ";
            } else {
                for (qint32 j = 0; j < 4 - tab; ++j) {
                    html += " ";
                }
            }
            tab = 0;
        } else {
            html += text[i];
            ++tab;
        }
    }
    return html.toHtmlEscaped();
}

QString ParseElement::generateOpenHtml() const {
    return "";
}

QString ParseElement::generateCloseHtml() const {
    return "";
}
