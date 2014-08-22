#include <QFont>
#include <QMessageBox>
#include <QInputDialog>
#include "setting.h"
#include "ColorSchemeWidget.h"
#include "ui_ColorSchemeWidget.h"

ColorSchemeWidget::ColorSchemeWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ColorSchemeWidget) {
    this->_schemeChanging = true;
    this->ui->setupUi(this);
    this->connect(this->ui->colorForeground, SIGNAL(colorChanged(QColor)),
                  this, SLOT(on_colorForeground_colorChanged(QColor)));
    this->connect(this->ui->colorBackground, SIGNAL(colorChanged(QColor)),
                  this, SLOT(on_colorBackground_colorChanged(QColor)));
    this->setup();
}

ColorSchemeWidget::~ColorSchemeWidget() {
    delete ui;
}

void ColorSchemeWidget::setup() {
    ColorSchemeSetting& colorScheme = Setting::instance()->colorScheme;
    for (auto schemeName : colorScheme.schemes().keys()) {
        this->ui->comboBoxScheme->addItem(schemeName);
    }
    this->ui->comboBoxScheme->setCurrentText(colorScheme.currentScheme());
    this->connect(this->ui->comboBoxScheme, SIGNAL(currentIndexChanged(QString)),
                  this, SLOT(updateColorScheme(QString)));
    this->updateColorScheme(colorScheme.currentScheme());
}

void ColorSchemeWidget::updateColorItem(QListWidgetItem *item) {
    if (item != nullptr) {
        ColorSchemeSetting& colorScheme = Setting::instance()->colorScheme;
        auto node = colorScheme.scheme().color(item->text());
        item->setTextColor(node.foreground());
        item->setBackgroundColor(node.background());
        QFont font;
        font.setFamily(colorScheme.fontFamily());
        font.setPointSize(colorScheme.fontSize());
        font.setBold(node.isBold());
        font.setItalic(node.isItalic());
        item->setFont(font);
    }
}

void ColorSchemeWidget::updateColorScheme(QString scheme) {
    ColorSchemeSetting& colorScheme = Setting::instance()->colorScheme;
    colorScheme.setCurrentScheme(scheme);
    this->ui->fontComboBox->setCurrentFont(QFont(colorScheme.fontFamily()));
    this->ui->spinBoxFontSize->setValue(colorScheme.fontSize());
    this->ui->listWidgetScheme->clear();
    for (auto nodeName : colorScheme.scheme().colors().keys()) {
        QListWidgetItem *item = new QListWidgetItem(nodeName);
        updateColorItem(item);
        this->ui->listWidgetScheme->addItem(item);
    }
    this->ui->listWidgetScheme->setCurrentRow(0);
    this->_schemeChanging = false;
}

void ColorSchemeWidget::on_fontComboBox_currentTextChanged(const QString &family) {
    if (not this->_schemeChanging) {
        Setting::instance()->colorScheme.scheme().setFontFamily(family);
        for (int i = 0; i < this->ui->listWidgetScheme->count(); ++i) {
            auto item = this->ui->listWidgetScheme->item(i);
            updateColorItem(item);
        }
    }
}

void ColorSchemeWidget::on_spinBoxFontSize_valueChanged(int size) {
    if (not this->_schemeChanging) {
        Setting::instance()->colorScheme.scheme().setFontSize(size);
        for (int i = 0; i < this->ui->listWidgetScheme->count(); ++i) {
            auto item = this->ui->listWidgetScheme->item(i);
            updateColorItem(item);
        }
    }
}

void ColorSchemeWidget::on_listWidgetScheme_currentRowChanged(int currentRow) {
    if (currentRow != -1) {
        ColorSchemeSetting& colorScheme = Setting::instance()->colorScheme;
        QListWidgetItem *item = this->ui->listWidgetScheme->currentItem();
        auto node = colorScheme.scheme().color(item->text());
        this->_colorChanging = true;
        this->ui->colorForeground->setColor(node.foreground());
        this->ui->colorBackground->setColor(node.background());
        this->ui->checkBoxBold->setChecked(node.isBold());
        this->ui->checkBoxItalic->setChecked(node.isItalic());
        this->_colorChanging = false;
    }
}


void ColorSchemeWidget::on_colorForeground_colorChanged(QColor color) {
    if (not this->_colorChanging) {
        ColorSchemeSetting& colorScheme = Setting::instance()->colorScheme;
        ColorScheme& scheme = colorScheme.scheme();
        QListWidgetItem *item = this->ui->listWidgetScheme->currentItem();
        if (item != nullptr) {
            scheme.setForeground(item->text(), color);
            updateColorItem(item);
        }
    }
}

void ColorSchemeWidget::on_colorBackground_colorChanged(QColor color) {
    if (not this->_colorChanging) {
        ColorSchemeSetting& colorScheme = Setting::instance()->colorScheme;
        ColorScheme& scheme = colorScheme.scheme();
        QListWidgetItem *item = this->ui->listWidgetScheme->currentItem();
        if (item != nullptr) {
            scheme.setBackground(item->text(), color);
            updateColorItem(item);
        }
    }
}

void ColorSchemeWidget::on_checkBoxBold_toggled(bool checked) {
    if (not this->_colorChanging) {
        ColorSchemeSetting& colorScheme = Setting::instance()->colorScheme;
        ColorScheme& scheme = colorScheme.scheme();
        QListWidgetItem *item = this->ui->listWidgetScheme->currentItem();
        if (item != nullptr) {
            scheme.setBold(item->text(), checked);
            updateColorItem(item);
        }
    }
}

void ColorSchemeWidget::on_checkBoxItalic_toggled(bool checked) {
    if (not this->_colorChanging) {
        ColorSchemeSetting& colorScheme = Setting::instance()->colorScheme;
        ColorScheme& scheme = colorScheme.scheme();
        QListWidgetItem *item = this->ui->listWidgetScheme->currentItem();
        if (item != nullptr) {
            scheme.setItalic(item->text(), checked);
            updateColorItem(item);
        }
    }
}

void ColorSchemeWidget::on_comboBoxScheme_currentIndexChanged(const QString &schemeName) {
    this->_schemeChanging = true;
    this->updateColorScheme(schemeName);
}

void ColorSchemeWidget::on_buttonCopy_clicked() {
    QString title = tr("Clone Color Scheme");
    QString label = tr("Input new color scheme name: ");
    QString text = this->ui->comboBoxScheme->currentText();
    bool ok;
    text = QInputDialog::getText(this, title, label, QLineEdit::Normal, text, &ok);
    if (ok) {
        ColorSchemeSetting& colorScheme = Setting::instance()->colorScheme;
        if (colorScheme.isSchemeExist(text)) {
            title = tr("Existed");
            text = tr("The name of the new color scheme is exited.");
            auto buttons = QMessageBox::Ok;
            auto defaultButton = QMessageBox::Ok;
            QMessageBox::information(this, title, text, buttons, defaultButton);
            return;
        }
        colorScheme.cloneScheme(text);
        this->ui->comboBoxScheme->addItem(text);
        this->ui->comboBoxScheme->setCurrentText(text);
    }
}

void ColorSchemeWidget::on_buttonDelete_clicked() {
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
        ColorSchemeSetting& colorScheme = Setting::instance()->colorScheme;
        colorScheme.deleteScheme(this->ui->comboBoxScheme->currentText());
        this->ui->comboBoxScheme->removeItem(this->ui->comboBoxScheme->currentIndex());
    }
}
