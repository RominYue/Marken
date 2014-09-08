#include "parse_line.h"
#include "parse_elem_horizontal.h"
using namespace std;

ParseElementHorizontal::ParseElementHorizontal() : ParseElementBlock() {
}

ParseElementType ParseElementHorizontal::type() const {
    return ParseElementType::TYPE_HORIZON;
}

bool ParseElementHorizontal::tryParse(const string &line, int offset, int& length) {
    int lineLen = line.length();
    if (lineLen > offset) {
        char ch = line[offset];
        if (ch == '*' || ch == '-' || ch == '_') {
            int num = 1;
            for (int index = offset + 1; index < lineLen; ++index) {
                if (line[index] == ch) {
                    ++num;
                } else if (!isspace(line[index])) {
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

string ParseElementHorizontal::generateOpenHtml() const {
    return "<hr />";
}

string ParseElementHorizontal::generateCloseHtml() const {
    return "";
}
