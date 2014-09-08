#include "parse_elem_code_inline.h"
using namespace std;

ParseElementCodeInline::ParseElementCodeInline() : ParseElementSpan() {
}

ParseElementType ParseElementCodeInline::type() const {
    return ParseElementType::TYPE_CODE_INLINE;
}

int ParseElementCodeInline::tryParse(const string& text, int offset) {
    if (text[offset] == '`') {
        int index = offset;
        int length = text.length();
        this->_backtickNum = 1;
        for (++index; index < length; ++index) {
            if (text[index] == '`') {
                ++this->_backtickNum;
            } else {
                break;
            }
        }
        int num = 0;
        bool escape = false;
        for (++index; index < length; ++index) {
            if (escape) {
                escape = false;
            } else {
                if (text[index] == '`') {
                    if (++num >= this->_backtickNum) {
                        return index + 1 - offset;
                    }
                } else {
                    num = 0;
                    if (text[index] == '\\') {
                        escape = true;
                    }
                }
            }
        }
    }
    return 0;
}

string ParseElementCodeInline::generateOpenHtml() const  {
    auto code = this->text.substr(this->_backtickNum, this->text.length() - this->_backtickNum * 2);
    return "<code>" + this->translateAmp(this->removeSideSpaces(code));
}

string ParseElementCodeInline::generateCloseHtml() const {
    return "</code>";
}
