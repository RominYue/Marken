#include "parse_elem_image.h"
using namespace std;

ParseElementImage::ParseElementImage() : ParseElementSpan(), ParseElementLink() {
}

string ParseElementImage::generateOpenImageHtml(const string& link, const string& alt, const string& title) const {
    string html = string("<img src=\"") + link + "\" alt=\"" + alt + "\"";
    if (title.length() > 0) {
        html += string(" title=\"") + title + "\"";
    }
    html += ">";
    return html;
}
