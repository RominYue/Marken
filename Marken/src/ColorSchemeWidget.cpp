#include <QFont>
#include "setting.h"
#include "ColorSchemeWidget.h"
#include "ui_ColorSchemeWidget.h"

ColorSchemeWidget::ColorSchemeWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ColorSchemeWidget) {
    this->ui->setupUi(this);
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

void ColorSchemeWidget::updateColorScheme(QString scheme) {
    ColorSchemeSetting& colorScheme = Setting::instance()->colorScheme;
    colorScheme.setCurrentScheme(scheme);
    this->ui->fontComboBox->setCurrentFont(QFont(colorScheme.fontFamily()));
    this->ui->spinBoxFontSize->setValue(colorScheme.fontSize());
    this->ui->listWidgetScheme->clear();
    for (auto nodeName : colorScheme.scheme().colors().keys()) {
        QListWidgetItem *item = new QListWidgetItem(nodeName);
        ColorSchemeNode node = colorScheme.scheme().colors().value(nodeName);
        QFont font;
        font.setFamily(colorScheme.fontFamily());
        font.setPointSize(colorScheme.fontSize());
        font.setBold(node.isBold());
        font.setItalic(node.isItalic());
        item->setFont(font);
        item->setTextColor(node.foreground());
        item->setBackgroundColor(node.background());
        this->ui->listWidgetScheme->addItem(item);
    }
}
