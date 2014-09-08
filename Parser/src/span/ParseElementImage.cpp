#include "ParseElementImage.h"

ParseElementImage::ParseElementImage() : ParseElementSpan(), ParseElementLink() {
}

QString ParseElementImage::generateOpenImageHtml(const QString& link, const QString& alt, const QString& title) const {
    QString html = QString("<img src=\"") + link + "\" alt=\"" + alt + "\"";
    if (title.length() > 0) {
        html += QString(" title=\"") + title + "\"";
    }
    html += ">";
    return html;
}
