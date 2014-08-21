#include "settingeditor.h"

SettingEditor::SettingEditor() {
}

SettingEditor::~SettingEditor() {
}

const QString& SettingEditor::fontFamily() const {
    return this->_schemes[this->_currentScheme].fontFamily();;
}

const QString& SettingEditor::fontFamily(const QString &schemeName) const {
    return this->_schemes[schemeName].fontFamily();
}

int SettingEditor::fontSize() const {
    return this->_schemes[this->_currentScheme].fontSize();
}

int SettingEditor::fontSize(const QString &schemeName) const {
    return this->_schemes[schemeName].fontSize();
}

const ColorScheme& SettingEditor::scheme() const {
    return this->_schemes.find(this->_currentScheme).value();
}

const ColorScheme& SettingEditor::scheme(const QString &schemeName) const {
    return this->_schemes.find(schemeName).value();
}
