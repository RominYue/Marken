#include "colorschemenode.h"

ColorSchemeNode::ColorSchemeNode() {
}

ColorSchemeNode::ColorSchemeNode(const QColor& foreground, const QColor& background, bool bold, bool italic) {
    this->_foreground = foreground;
    this->_background = background;
    this->_bold = bold;
    this->_italic = italic;
}

ColorSchemeNode::~ColorSchemeNode() {
}

const QColor& ColorSchemeNode::foreground() const {
    return this->_foreground;
}

const QColor& ColorSchemeNode::background() const {
    return this->_background;
}

bool ColorSchemeNode::isBold() const {
    return this->_bold;
}

bool ColorSchemeNode::isItalic() const {
    return this->_italic;
}

void ColorSchemeNode::setForeground(const QColor &color) {
    this->_foreground = color;
}

void ColorSchemeNode::setBackground(const QColor &color) {
    this->_background = color;
}

void ColorSchemeNode::setBold(bool value) {
    this->_bold = value;
}

void ColorSchemeNode::setItalic(bool value) {
    this->_italic = value;
}
