#include "ParseLineData.h"
#include "ParseElementList.h"

ParseElementList::ParseElementList() : ParseElementBlock() {
}

bool ParseElementList::inheritable() const {
    return true;
}

QString ParseElementList::generateOpenHtml() const {
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

QString ParseElementList::generateCloseHtml() const {
    if (parent->next() == nullptr) {
        return "</li>" + this->getListCloseTag();
    }
    auto elem = parent->next()->getElementAt(offset);
    if (elem == nullptr || elem->type() != this->type()) {
        return "</li>" + this->getListCloseTag();
    }
    if (!qSharedPointerDynamicCast<ParseElementBlock>(elem)->isVirtual) {
        return "</li>";
    }
    return "";
}

QString ParseElementList::getListOpenTag() const {
    return "";
}

QString ParseElementList::getListCloseTag() const {
    return "";
}
