#include <QDomDocument>
#include <QDomElement>
#include <QFile>
#include <QTextStream>
#include "ColorSchemeSetting.h"

ColorSchemeSetting::ColorSchemeSetting() {
    this->load();
}

ColorSchemeSetting::~ColorSchemeSetting() {
}

const QString& ColorSchemeSetting::fontFamily() const {
    return this->_schemes[this->_currentScheme].fontFamily();;
}

const QString& ColorSchemeSetting::fontFamily(const QString &schemeName) const {
    return this->_schemes[schemeName].fontFamily();
}

int ColorSchemeSetting::fontSize() const {
    return this->_schemes[this->_currentScheme].fontSize();
}

int ColorSchemeSetting::fontSize(const QString &schemeName) const {
    return this->_schemes[schemeName].fontSize();
}

ColorScheme &ColorSchemeSetting::scheme() {
    return this->_schemes.find(this->_currentScheme).value();
}

ColorScheme& ColorSchemeSetting::scheme(const QString &schemeName) {
    return this->_schemes.find(schemeName).value();
}

void ColorSchemeSetting::setCurrentScheme(const QString &schemeName) {
    this->_currentScheme = schemeName;
}

const QString& ColorSchemeSetting::currentScheme() const {
    return this->_currentScheme;
}

QMap<QString, ColorScheme> &ColorSchemeSetting::schemes() {
    return this->_schemes;
}

int ColorSchemeSetting::char2int(QChar c) const {
    int v = (int)c.toUpper().toLatin1();
    if (v >= '0' && v <= '9') {
        return v - '0';
    }
    return v - 'A' + 10;
}

char ColorSchemeSetting::int2char(int val) const {
    if (val < 10) {
        return '0' + val;
    }
    return 'A' + val - 10;
}

int ColorSchemeSetting::hex2int(QChar a, QChar b) const {
    return char2int(a) * 16 + char2int(b);
}

QString ColorSchemeSetting::int2hex(int val) const {
    return QString("%1%2").arg(int2char(val / 16)).arg(int2char(val % 16));
}

QColor ColorSchemeSetting::str2color(const QString &str) const {
    QColor color;
    if (str.length() == 7) {
        color.setRed(hex2int(str.at(1), str.at(2)));
        color.setGreen(hex2int(str.at(3), str.at(4)));
        color.setBlue(hex2int(str.at(5), str.at(6)));
    }
    return color;
}

QString ColorSchemeSetting::color2str(const QColor &color) const {
    QString str = "#";
    str += int2hex(color.red());
    str += int2hex(color.green());
    str += int2hex(color.blue());
    return str;
}

void ColorSchemeSetting::load() {
    QFile file("style/colorscheme.xml");
    if (not file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        return;
    }
    QDomDocument document;
    document.setContent(&file);
    QDomElement editor = document.documentElement();
    this->_currentScheme = editor.attribute("scheme", "Default");
    this->_schemes.clear();
    for (auto schemeElement = editor.firstChildElement();
         not schemeElement.isNull();
         schemeElement = schemeElement.nextSiblingElement()) {
        QString schemeName = schemeElement.attribute("name");
        ColorScheme scheme;
        scheme.setFontFamily(schemeElement.attribute("family"));
        scheme.setFontSize(schemeElement.attribute("size").toInt());
        for (auto colorElement = schemeElement.firstChildElement();
             not colorElement.isNull();
             colorElement = colorElement.nextSiblingElement()) {
            QString nodeName = colorElement.attribute("name");
            ColorSchemeNode node;
            node.setForeground(str2color(colorElement.firstChildElement("foreground").text()));
            node.setBackground(str2color(colorElement.firstChildElement("background").text()));
            node.setBold(colorElement.firstChildElement("bold").text() == "true");
            node.setItalic(colorElement.firstChildElement("italic").text() == "true");
            scheme.setColor(nodeName, node);
        }
        this->_schemes[schemeName] = scheme;
    }
    file.close();
}

void ColorSchemeSetting::save() {
    QDomDocument document;
    QDomElement editor = document.createElement("editor");
    editor.setAttribute("scheme", this->_currentScheme);
    for (auto schemeKey : this->_schemes.keys()) {
        QDomElement schemeElement = document.createElement("scheme");
        schemeElement.setAttribute("name", schemeKey);
        ColorScheme& scheme = this->_schemes.find(schemeKey).value();
        schemeElement.setAttribute("family", scheme.fontFamily());
        schemeElement.setAttribute("size", scheme.fontSize());
        for (auto nodeKey : scheme.colors().keys()) {
            QDomElement nodeElement = document.createElement("node");
            nodeElement.setAttribute("name", nodeKey);
            ColorSchemeNode node = scheme.colors().find(nodeKey).value();
            QDomText text;
            QDomElement foreground = document.createElement("foreground");
            text = document.createTextNode(color2str(node.foreground()));
            foreground.appendChild(text);
            QDomElement background = document.createElement("background");
            text = document.createTextNode(color2str(node.background()));
            background.appendChild(text);
            QDomElement bold = document.createElement("bold");
            text = document.createTextNode(node.isBold() ? "true" : "false");
            bold.appendChild(text);
            QDomElement italic = document.createElement("italic");
            text = document.createTextNode(node.isItalic() ? "true" : "false");
            italic.appendChild(text);
            nodeElement.appendChild(foreground);
            nodeElement.appendChild(background);
            nodeElement.appendChild(bold);
            nodeElement.appendChild(italic);
            schemeElement.appendChild(nodeElement);
        }
        editor.appendChild(schemeElement);
    }
    document.appendChild(editor);
    QFile file("style/colorscheme.xml");
    if (not file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        return;
    }
    QTextStream out(&file);
    out.setCodec("UTF-8");
    document.save(out, 2);
    file.close();
}

bool ColorSchemeSetting::isSchemeExist(const QString &schemeName) const {
    for (auto name : this->_schemes.keys()) {
        if (name == schemeName) {
            return true;
        }
    }
    return false;
}

void ColorSchemeSetting::cloneScheme(const QString &clone) {
    auto scheme = this->scheme();
    ColorScheme cloneScheme;
    cloneScheme.setFontFamily(scheme.fontFamily());
    cloneScheme.setFontSize(scheme.fontSize());
    for (auto nodeName : scheme.colors().keys()) {
        auto node = scheme.colors().value(nodeName);
        ColorSchemeNode cloneNode;
        cloneNode.setForeground(node.foreground());
        cloneNode.setBackground(node.background());
        cloneNode.setBold(node.isBold());
        cloneNode.setItalic(node.isItalic());
        cloneScheme.setColor(nodeName, cloneNode);
    }
    this->_schemes[clone] = cloneScheme;
}

void ColorSchemeSetting::deleteScheme(const QString &schemeName) {
    this->_schemes.remove(schemeName);
    this->_currentScheme = this->_schemes.keys()[0];
}
