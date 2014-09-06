#include <QMessageBox>
#include <QInputDialog>
#include <QListWidgetItem>
#include "Setting.h"
#include "ColorWidget.h"
#include "ColorSchemeForm.h"
#include "ui_ColorSchemeForm.h"

ColorSchemeForm::ColorSchemeForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ColorSchemeForm) {
    ui->setupUi(this);
    this->connect(this->ui->colorWidgetForeground, SIGNAL(colorChanged(QColor)), this, SLOT(colorWidgetForeground_changed(QColor)));
    this->connect(this->ui->colorWidgetBackground, SIGNAL(colorChanged(QColor)), this, SLOT(colorWidgetBackground_changed(QColor)));
    this->setup();
}

ColorSchemeForm::~ColorSchemeForm() {
    delete ui;
    ColorSchemeSetting& setting = Setting::instance()->colorSetting;
    setting.save();
}

void ColorSchemeForm::setup() {
    ColorSchemeSetting& setting = Setting::instance()->colorSetting;
    auto nameList = setting.nameList();
    for (auto name : nameList) {
        this->ui->comboBoxScheme->addItem(name);
    }
    this->ui->comboBoxScheme->setCurrentText(setting.name());
    this->updateColorScheme();
}

void ColorSchemeForm::updateColorScheme() {
    this->_schemeChanging = true;
    ColorSchemeSetting& setting = Setting::instance()->colorSetting;
    ColorScheme& scheme = setting.colorScheme();
    this->ui->fontComboBox->setCurrentFont(QFont(scheme.fontFamily()));
    this->ui->spinBoxSize->setValue(scheme.fontSize());
    this->ui->listWidgetScheme->clear();
    auto typeList = scheme.typeList();
    for (auto type : typeList) {
        QListWidgetItem* item = new QListWidgetItem(scheme.name(type));
        this->updateColorItem(item);
        this->ui->listWidgetScheme->addItem(item);
    }
    this->ui->listWidgetScheme->setCurrentRow(0);
    this->_schemeChanging = false;
}

void ColorSchemeForm::updateColorItem(QListWidgetItem *item) {
    if (item != nullptr) {
        ColorSchemeSetting& setting = Setting::instance()->colorSetting;
        ColorScheme& scheme = setting.colorScheme();
        auto type = scheme.type(item->text());
        item->setTextColor(scheme.foreground(type));
        item->setBackgroundColor(scheme.background(type));
        QFont font;
        font.setFamily(scheme.fontFamily());
        font.setPointSize(scheme.fontSize());
        font.setBold(scheme.bold(type));
        font.setItalic(scheme.italic(type));
        font.setUnderline(scheme.underline(type));
        font.setStrikeOut(scheme.strikeout(type));
        item->setFont(font);
    }
}

void ColorSchemeForm::on_fontComboBox_currentIndexChanged(const QString &family) {
    if (!this->_schemeChanging) {
        ColorSchemeSetting& setting = Setting::instance()->colorSetting;
        ColorScheme& scheme = setting.colorScheme();
        scheme.setFontFamily(family);
        for (int i = 0; i < this->ui->listWidgetScheme->count(); ++i) {
            auto item = this->ui->listWidgetScheme->item(i);
            this->updateColorItem(item);
        }
    }
}

void ColorSchemeForm::on_spinBoxSize_valueChanged(int size) {
    if (!this->_schemeChanging) {
        ColorSchemeSetting& setting = Setting::instance()->colorSetting;
        ColorScheme& scheme = setting.colorScheme();
        scheme.setFontSize(size);
        for (int i = 0; i < this->ui->listWidgetScheme->count(); ++i) {
            auto item = this->ui->listWidgetScheme->item(i);
            this->updateColorItem(item);
        }
    }
}

void ColorSchemeForm::on_comboBoxScheme_currentIndexChanged(const QString &scheme) {
    ColorSchemeSetting& setting = Setting::instance()->colorSetting;
    setting.selectScheme(scheme);
    this->updateColorScheme();
}

void ColorSchemeForm::on_pushButtonCopy_clicked() {
    QString title = tr("Clone Color Scheme");
    QString label = tr("Input new color scheme name: ");
    QString text = this->ui->comboBoxScheme->currentText();
    bool ok;
    text = QInputDialog::getText(this, title, label, QLineEdit::Normal, text, &ok);
    if (ok) {
        ColorSchemeSetting& setting = Setting::instance()->colorSetting;
        if (!setting.copyScheme(text)) {
            title = tr("Existed");
            text = tr("The name of the new color scheme is exited.");
            auto buttons = QMessageBox::Ok;
            auto defaultButton = QMessageBox::Ok;
            QMessageBox::information(this, title, text, buttons, defaultButton);
            return;
        }
        this->ui->comboBoxScheme->addItem(text);
        this->ui->comboBoxScheme->setCurrentText(text);
    }
}

void ColorSchemeForm::on_pushButtonDelete_clicked() {
    if (this->ui->comboBoxScheme->count() == 1) {
        QString title = tr("Prevent Deleting");
        QString text = tr("You cannot delete the last color scheme.");
        auto buttons = QMessageBox::Ok;
        auto defaultButton = QMessageBox::Ok;
        QMessageBox::information(this, title, text, buttons, defaultButton);
        return;
    }
    QString title = tr("Delete Color Scheme");
    QString text = tr("Are you sure to delete the selected color scheme?");
    auto buttons = QMessageBox::Yes | QMessageBox::No;
    auto defaultButton = QMessageBox::Yes;
    if (QMessageBox::warning(this, title, text, buttons, defaultButton) == QMessageBox::Yes) {
        ColorSchemeSetting& setting = Setting::instance()->colorSetting;
        setting.deleteScheme(this->ui->comboBoxScheme->currentText());
        this->ui->comboBoxScheme->removeItem(this->ui->comboBoxScheme->currentIndex());
    }
}

void ColorSchemeForm::on_listWidgetScheme_currentRowChanged(int currentRow) {
    if (currentRow != -1) {
        this->_colorChanging = true;
        ColorSchemeSetting& setting = Setting::instance()->colorSetting;
        ColorScheme& scheme = setting.colorScheme();
        auto item = this->ui->listWidgetScheme->currentItem();
        auto type = scheme.type(item->text());
        this->ui->colorWidgetForeground->setColor(scheme.foreground(type));
        this->ui->colorWidgetBackground->setColor(scheme.background(type));
        this->ui->checkBoxBold->setChecked(scheme.bold(type));
        this->ui->checkBoxItalic->setChecked(scheme.italic(type));
        this->ui->checkBoxUnderline->setChecked(scheme.underline(type));
        this->ui->checkBoxStrikeout->setChecked(scheme.strikeout(type));
        this->_colorChanging = false;
    }
}

void ColorSchemeForm::on_checkBoxBold_toggled(bool checked) {
    if (!this->_colorChanging) {
        ColorSchemeSetting& setting = Setting::instance()->colorSetting;
        ColorScheme& scheme = setting.colorScheme();
        auto item = this->ui->listWidgetScheme->currentItem();
        auto type = scheme.type(item->text());
        scheme.setBold(type, checked);
        this->updateColorItem(item);
    }
}

void ColorSchemeForm::on_checkBoxItalic_toggled(bool checked) {
    if (!this->_colorChanging) {
        ColorSchemeSetting& setting = Setting::instance()->colorSetting;
        ColorScheme& scheme = setting.colorScheme();
        auto item = this->ui->listWidgetScheme->currentItem();
        auto type = scheme.type(item->text());
        scheme.setItalic(type, checked);
        this->updateColorItem(item);
    }
}

void ColorSchemeForm::on_checkBoxUnderline_toggled(bool checked) {
    if (!this->_colorChanging) {
        ColorSchemeSetting& setting = Setting::instance()->colorSetting;
        ColorScheme& scheme = setting.colorScheme();
        auto item = this->ui->listWidgetScheme->currentItem();
        auto type = scheme.type(item->text());
        scheme.setUnderline(type, checked);
        this->updateColorItem(item);
    }
}

void ColorSchemeForm::on_checkBoxStrikeout_toggled(bool checked) {
    if (!this->_colorChanging) {
        ColorSchemeSetting& setting = Setting::instance()->colorSetting;
        ColorScheme& scheme = setting.colorScheme();
        auto item = this->ui->listWidgetScheme->currentItem();
        auto type = scheme.type(item->text());
        scheme.setStrikeout(type, checked);
        this->updateColorItem(item);
    }
}

void ColorSchemeForm::colorWidgetForeground_changed(QColor color) {
    if (!this->_colorChanging) {
        ColorSchemeSetting& setting = Setting::instance()->colorSetting;
        ColorScheme& scheme = setting.colorScheme();
        auto item = this->ui->listWidgetScheme->currentItem();
        auto type = scheme.type(item->text());
        scheme.setForeground(type, color);
        this->updateColorItem(item);
    }
}

void ColorSchemeForm::colorWidgetBackground_changed(QColor color) {
    if (!this->_colorChanging) {
        ColorSchemeSetting& setting = Setting::instance()->colorSetting;
        ColorScheme& scheme = setting.colorScheme();
        auto item = this->ui->listWidgetScheme->currentItem();
        auto type = scheme.type(item->text());
        scheme.setBackground(type, color);
        this->updateColorItem(item);
    }
}
