#include "parse_line.h"
#include "parse_elem_list_ordered.h"
using namespace std;

ParseElementListOrdered::ParseElementListOrdered() : ParseElementList() {
}

ParseElementType ParseElementListOrdered::type() const {
    return ParseElementType::TYPE_LIST_ORDERED;
}

bool ParseElementListOrdered::tryParse(const string &line, int offset, int& length) {
    int lineLen = line.length();
    if (lineLen > offset) {
        if (line[offset] == ' ' || line[offset] == '\t') {
            if (parent->prev() == nullptr) {
                return false;
            }
            if (parent->prev()->getTypeAt(offset) == ParseElementType::TYPE_LIST_ORDERED) {
                this->isVirtual = true;
                length = 1;
                return true;
            }
        } else if (isdigit(line[offset])) {
            int index = offset;
            for (++index; index < lineLen; ++index) {
                if (!isdigit(line[index])) {
                    break;
                }
            }
            if (index == lineLen) {
                return false;
            }
            if (line[index] == '.') {
                this->isVirtual = false;
                length = index + 1 - offset;
                return true;
            }
        }
    }
    return false;
}

string ParseElementListOrdered::getListOpenTag() const {
    return "<ol>";
}

string ParseElementListOrdered::getListCloseTag() const {
    return "</ol>";
}
