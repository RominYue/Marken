#include "parse_line.h"
#include "parse_elem_list.h"
using namespace std;

ParseElementList::ParseElementList() : ParseElementBlock() {
}

bool ParseElementList::inheritable() const {
	return true;
}

string ParseElementList::generateOpenHtml() const {
    if (parent->prev() == nullptr) {
        return this->getListOpenTag() + "<li>";
    }
    auto elem = parent->prev()->getElementAt(offset);
    if (elem == nullptr || elem->type() != this->type()) {
        return this->getListOpenTag() + "<li>";
    }
    if (!this->isVirtual) {
        return "<li>";
    }
    return "";
}

string ParseElementList::generateCloseHtml() const {
    if (parent->next() == nullptr) {
        return "</li>" + this->getListCloseTag();
    }
    auto elem = parent->next()->getElementAt(offset);
    if (elem == nullptr || elem->type() != this->type()) {
        return "</li>" + this->getListCloseTag();
    }
    if (!dynamic_pointer_cast<ParseElementBlock>(elem)->isVirtual) {
        return "</li>";
    }
    return "";
}

string ParseElementList::getListOpenTag() const {
    return "";
}

string ParseElementList::getListCloseTag() const {
    return "";
}
