#include "ParseLineData.h"
#include "ParseElementHorizontal.h"

ParseElementHorizontal::ParseElementHorizontal() : ParseElementBlock() {
}

ParseElementType ParseElementHorizontal::type() const {
    return ParseElementType::TYPE_HORIZON;
}

bool ParseElementHorizontal::tryParse(const QString &line, int offset, int& length) {
    int lineLen = line.length();
    if (lineLen > offset) {
        QChar ch = line[offset];
        if (ch == '*' || ch == '-' || ch == '_') {
            int num = 1;
            for (int index = offset + 1; index < lineLen; ++index) {
                if (line[index] == ch) {
                    ++num;
                } else if (!line[index].isSpace()) {
                    return false;
                }
            }
            if (num >= 3) {
                length = lineLen - offset;
                return true;
            }
        }
    }
    return false;
}

QString ParseElementHorizontal::generateOpenHtml() const {
    return "<hr />";
}

QString ParseElementHorizontal::generateCloseHtml() const {
    return "";
}
