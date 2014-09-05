#include <QFile>
#include <QTextStream>
#include <QDomDocument>
#include <QDomElement>
#include "ColorScheme.h"

ColorScheme::ColorScheme() {
    this->_type["Default"] = ParseElementType::TYPE_PARAGRAPH;
    this->_type["HTML Block"] = ParseElementType::TYPE_HTML_BLOCK;
    this->_type["Code Block"] = ParseElementType::TYPE_CODE_BLOCK;
    this->_type["Header Atx"] = ParseElementType::TYPE_HEADER_ATX;
    this->_type["Header Setext"] = ParseElementType::TYPE_HEADER_SETEXT;
    this->_type["Horizontal Rule"] = ParseElementType::TYPE_HORIZON;
    this->_type["Block Quote"] = ParseElementType::TYPE_QUOTE;
    this->_type["List Unordered"] = ParseElementType::TYPE_LIST_UNORDERED;
    this->_type["List Ordered"] = ParseElementType::TYPE_LIST_ORDERED;
    this->_type["Escape"] = ParseElementType::TYPE_ESCAPE;
    this->_type["HTML Amp"] = ParseElementType::TYPE_AMP;
    this->_type["HTML Inline"] = ParseElementType::TYPE_HTML_INLINE;
    this->_type["Code Inline"] = ParseElementType::TYPE_CODE_INLINE;
    this->_type["Emphasis"] = ParseElementType::TYPE_EMPHASIS;
    this->_type["Strong"] = ParseElementType::TYPE_STRONG;
    this->_type["Image Inline"] = ParseElementType::TYPE_IMAGE_INLINE;
    this->_type["Image Reference"] = ParseElementType::TYPE_IMAGE_REFERENCE;
    this->_type["Link Inline"] = ParseElementType::TYPE_LINK_INLINE;
    this->_type["Link Reference"] = ParseElementType::TYPE_LINK_REFERENCE;
    this->_type["Link Label"] = ParseElementType::TYPE_LINK_LABEL;
    this->_type["Link Automatic"] = ParseElementType::TYPE_LINK_AUTOMATIC;
}

ColorScheme::~ColorScheme() {
}

void ColorScheme::save(const QString& path) {
    QDomDocument document;
    QDomElement schemeElement = document.createElement("scheme");
    schemeElement.setAttribute("family", this->fontFamily());
    schemeElement.setAttribute("size", this->fontSize());
    for (auto type : this->_foreground.keys()) {
        QDomElement nodeElement = document.createElement("node");
        nodeElement.setAttribute("name", this->name(type));
        nodeElement.setAttribute("foreground", this->foreground(type).name());
        nodeElement.setAttribute("background", this->background(type).name());
        nodeElement.setAttribute("bold", (int)this->bold(type));
        nodeElement.setAttribute("italic", (int)this->italic(type));
        nodeElement.setAttribute("underline", (int)this->underline(type));
        nodeElement.setAttribute("strikeout", (int)this->strikeout(type));
        schemeElement.appendChild(nodeElement);
    }
    document.appendChild(schemeElement);
    QFile file(path);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        return;
    }
    QTextStream out(&file);
    out.setCodec("UTF-8");
    document.save(out, 2);
    file.close();
}

void ColorScheme::load(const QString& path) {
    QFile file(path);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        return;
    }
    QDomDocument document;
    document.setContent(&file);
    QDomElement schemeElement = document.documentElement();
    for (auto nodeElement = schemeElement.firstChildElement();
         !nodeElement.isNull();
         nodeElement = nodeElement.nextSiblingElement()) {
        auto type = this->_type[nodeElement.attribute("name")];
        this->setForeground(type, QColor(nodeElement.attribute("foreground")));
        this->setBackground(type, QColor(nodeElement.attribute("backgrond")));
        this->setBold(type, nodeElement.attribute("bold").toInt());
        this->setItalic(type, nodeElement.attribute("italic").toInt());
        this->setUnderline(type, nodeElement.attribute("underline").toInt());
        this->setStrikeout(type, nodeElement.attribute("strikeout").toInt());
    }
    this->setFontFamily(schemeElement.attribute("family"));
    this->setFontSize(schemeElement.attribute("size").toInt());
}

ParseElementType ColorScheme::type(const QString& name) const {
    return this->_type.find(name).value();
}

const QString ColorScheme::name(const ParseElementType type) const {
    for (auto name : this->_type.keys()) {
        if (this->_type.find(name).value() == type) {
            return name;
        }
    }
    return "";
}

QList<ParseElementType> ColorScheme::typeList() const {
    return this->_bold.keys();
}

const QString& ColorScheme::fontFamily() const {
    return this->_fontFamily;
}

int ColorScheme::fontSize() const {
    return this->_fontSize;
}

const QColor& ColorScheme::foreground(const ParseElementType type) const {
    return this->_foreground.find(type).value();
}

const QColor& ColorScheme::background(const ParseElementType type) const {
    return this->_background.find(type).value();
}

bool ColorScheme::bold(const ParseElementType type) const {
    return this->_bold.find(type).value();
}

bool ColorScheme::italic(const ParseElementType type) const {
    return this->_italic.find(type).value();
}

bool ColorScheme::underline(const ParseElementType type) const {
    return this->_underline.find(type).value();
}

bool ColorScheme::strikeout(const ParseElementType type) const {
    return this->_strikeout.find(type).value();
}

QTextCharFormat ColorScheme::format(const ParseElementType type) const {
    return this->_format.find(type).value();
}

void ColorScheme::setFontFamily(const QString &family) {
    this->_fontFamily = family;
    for (auto it = this->_format.begin(); it != this->_format.end(); ++it) {
        it.value().setFontFamily(family);
    }
}

void ColorScheme::setFontSize(const int size) {
    this->_fontSize = size;
    for (auto it = this->_format.begin(); it != this->_format.end(); ++it) {
        it.value().setFontPointSize(size);
    }
}

void ColorScheme::setForeground(const ParseElementType type, const QColor &color) {
    this->_foreground[type] = color;
    this->_format[type].setForeground(color);
}

void ColorScheme::setBackground(const ParseElementType type, const QColor &color) {
    this->_background[type] = color;
    this->_format[type].setBackground(color);
}

void ColorScheme::setBold(const ParseElementType type, const bool val) {
    this->_bold[type] = val;
    if (val) {
        this->_format[type].setFontWeight(QFont::Bold);
    } else {
        this->_format[type].setFontWeight(QFont::Normal);
    }
}

void ColorScheme::setItalic(const ParseElementType type, const bool val) {
    this->_italic[type] = val;
    this->_format[type].setFontItalic(val);
}

void ColorScheme::setUnderline(const ParseElementType type, const bool val) {
    this->_underline[type] = val;
    this->_format[type].setFontUnderline(val);
}

void ColorScheme::setStrikeout(const ParseElementType type, const bool val) {
    this->_strikeout[type] = val;
    this->_format[type].setFontStrikeOut(val);
}
