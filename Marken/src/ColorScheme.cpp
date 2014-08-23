#include "ColorScheme.h"

ColorScheme::ColorScheme() {
}

ColorScheme::~ColorScheme() {
}

const QString& ColorScheme::fontFamily() const {
    return this->_fontFamily;
}

int ColorScheme::fontSize() const {
    return this->_fontSize;
}

QMap<QString, ColorSchemeNode> &ColorScheme::colors() {
    return this->_colors;
}

ColorSchemeNode& ColorScheme::color() {
    return this->color("Default");
}

ColorSchemeNode& ColorScheme::color(const QString &section) {
    return this->_colors.find(section).value();
}

void ColorScheme::setFontFamily(const QString &family) {
    this->_fontFamily = family;
}

void ColorScheme::setFontSize(int size) {
    this->_fontSize = size;
}

void ColorScheme::setColor(const QString &section, const ColorSchemeNode &color) {
    this->_colors[section] = color;
}

void ColorScheme::setForeground(const QString &section, const QColor &foreground) {
    this->_colors[section].setForeground(foreground);
}

void ColorScheme::setBackground(const QString &section, const QColor &background) {
    this->_colors[section].setBackground(background);
}

void ColorScheme::setBold(const QString &section, bool value) {
    this->_colors[section].setBold(value);
}

void ColorScheme::setItalic(const QString &section, bool value) {
    this->_colors[section].setItalic(value);
}
