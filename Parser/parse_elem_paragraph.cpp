#include "parse_elem_paragraph.h"
using namespace std;

ParseElemParagraph::ParseElemParagraph() :
    ParseElemBlock() {
}

ParseElemType ParseElemParagraph::type() const {
    return ParseElemType::ELEM_PARAGRAPH;
}

bool ParseElemParagraph::tryParse(std::string text, int offset, int &len) {

}

string ParseElemParagraph::generateOpenHtml() const {
    return "<p>";
}

string ParseElemParagraph::generateCloseHtml() const {
    return "</p>";
}
