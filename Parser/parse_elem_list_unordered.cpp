#include "parse_line.h"
#include "parse_elem_list_unordered.h"
using namespace std;

ParseElementListUnordered::ParseElementListUnordered() : ParseElementList() {
}

ParseElementType ParseElementListUnordered::type() const {
    return ParseElementType::TYPE_LIST_UNORDERED;
}

bool ParseElementListUnordered::tryParse(const string &line, int offset, int& length) {
	int lineLen = line.length();
	if (lineLen > offset) {
        if (line[offset] == ' ' || line[offset] == '\t') {
            if (parent->prev() == nullptr) {
                return false;
            }
            if (parent->prev()->getTypeAt(offset) == ParseElementType::TYPE_LIST_UNORDERED) {
                this->isVirtual = true;
                length = 1;
                return true;
            }
        } else if (line[offset] == '*' || line[offset] == '+' || line[offset] == '-') {
            if (offset + 1 == lineLen || line[offset + 1] == ' ' || line[offset + 1] == '\t') {
                this->isVirtual = false;
                length = 1;
                return true;
            }
        }
	}
	return false;
}

string ParseElementListUnordered::getListOpenTag() const {
    return "<ul>";
}

string ParseElementListUnordered::getListCloseTag() const {
    return "</ul>";
}
