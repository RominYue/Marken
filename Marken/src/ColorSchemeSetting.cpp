#include <QFile>
#include <QTextStream>
#include <QDomDocument>
#include <QDomElement>
#include "ColorScheme.h"
#include "ColorSchemeSetting.h"

ColorSchemeSetting::ColorSchemeSetting() {
}

ColorSchemeSetting::~ColorSchemeSetting() {
}

void ColorSchemeSetting::save() {
    QDomDocument document;
    QDomElement schemeElement = document.createElement("scheme");
    schemeElement.setAttribute("select", this->name());
    for (auto name : this->_nameList) {
        QDomElement nodeElement = document.createElement("node");
        nodeElement.setAttribute("name", name);
        schemeElement.appendChild(nodeElement);
    }
    document.appendChild(schemeElement);
    QFile file("style/colorscheme.xml");
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        return;
    }
    QTextStream out(&file);
    out.setCodec("UTF-8");
    document.save(out, 2);
    file.close();
    this->saveScheme();
}

void ColorSchemeSetting::load() {
    QFile file("style/colorscheme.xml");
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        return;
    }
    QDomDocument document;
    document.setContent(&file);
    QDomElement schemeElement = document.documentElement();
    this->_name = schemeElement.attribute("select");
    for (auto nodeElement = schemeElement.firstChildElement();
         !nodeElement.isNull();
         nodeElement = nodeElement.nextSiblingElement()) {
        this->_nameList.push_back(nodeElement.attribute("name"));
    }
    this->loadScheme();
}

const QString& ColorSchemeSetting::name() const {
    return this->_name;
}

const QList<QString>& ColorSchemeSetting::nameList() const {
    return this->_nameList;
}

void ColorSchemeSetting::selectScheme(const QString& name) {
    if (!this->_name.isEmpty()) {
        this->saveScheme();
    }
    this->_name = name;
    this->loadScheme();
}

bool ColorSchemeSetting::copyScheme(const QString& name) {
    for (auto exist : this->_nameList) {
        if (exist.toLower() == name.toLower()) {
            return false;
        }
    }
    this->_name = name;
    this->saveScheme();
    return true;
}

bool ColorSchemeSetting::deleteScheme(const QString& name) {
    if (this->_nameList.size() <= 1) {
        return false;
    }
    for (int i = 0; i < name.size(); ++i) {
        if (this->_nameList[i].toLower() == name.toLower()) {
            this->_nameList.removeAt(i);
            return true;
        }
    }
    return false;
}

ColorScheme& ColorSchemeSetting::colorScheme() {
    return this->_scheme;
}

void ColorSchemeSetting::saveScheme() {
    this->_scheme.save("style/color_" + this->_name.toLower() + ".xml");
}

void ColorSchemeSetting::loadScheme() {
    this->_scheme.load("style/color_" + this->_name.toLower() + ".xml");
}
