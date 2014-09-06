#include <cstdio>
#include <string>
#include <QDir>
#include <QFile>
#include <QFileInfo>
#include <QTextStream>
#include <QTextBlock>
#include <QWebFrame>
#include "parse_elem_block.h"
#include "Setting.h"
#include "BlockData.h"
#include "Preview.h"
#include "ui_Preview.h"
using namespace std;

Preview::Preview(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Preview) {
    ui->setupUi(this);
    this->updateColorScheme();
    this->ui->webView->settings()->setDefaultTextEncoding("UTF-8");
}

Preview::~Preview() {
    delete ui;
}

void Preview::updateColorScheme() {
    ColorSchemeSetting& setting = Setting::instance()->colorSetting;
    ColorScheme& scheme = setting.colorScheme();
    this->ui->webView->settings()->setFontFamily(QWebSettings::StandardFont, scheme.fontFamily());
    this->ui->webView->settings()->setFontSize(QWebSettings::DefaultFontSize, scheme.fontSize());
}

void Preview::scrollToLine(int lineNum) {
    if (this->_lineAnchors.find(lineNum) != this->_lineAnchors.end()) {
        QString url = QUrl::fromLocalFile(this->_tempName).toString() + "#" + this->getLineNumAnchor(lineNum);
        this->ui->webView->setUrl(url);
    }
}

void Preview::showPreview(Editor *editor) {
    if (editor == nullptr) {
        this->ui->webView->setHtml("");
        return;
    }
    QString html;
    auto block = editor->document()->firstBlock();
    int lineNum = 0;
    bool isCode = false;
    this->_lineAnchors.clear();
    while (block.isValid()) {
        auto data = dynamic_cast<BlockData*>(block.userData())->data();
        if (data->blocks.size() == 0) {
            isCode = false;
        } else if ((*data->blocks.rbegin())->type() != ParseElementType::TYPE_CODE_BLOCK) {
            isCode = false;
        }
        ++lineNum;
        if (!isCode) {
            this->_lineAnchors.insert(lineNum);
            html += "<a href=\"#\" id=\"" + this->getLineNumAnchor(lineNum) + "\"> </a> ";
        }
        html += QString::fromUtf8(data->generateHtml().c_str()) + "\n";
        if (data->blocks.size() > 0) {
            if ((*data->blocks.rbegin())->type() == ParseElementType::TYPE_CODE_BLOCK) {
                isCode = true;
            }
        }
        block = block.next();
    }
    QDir dir("temp");
    if (!dir.exists()) {
        dir.mkdir(".");
    }
    QFileInfo info("temp/" + editor->name() + ".html");
    this->_tempName = info.absoluteFilePath();
    QFile file(this->_tempName);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        return;
    }
    QTextStream fout(&file);
    fout.setCodec("UTF-8");
    fout << html;
    file.close();
    this->ui->webView->setUrl(QUrl::fromLocalFile(this->_tempName));
}

void Preview::changePreview(Editor *editor) {
    if (editor == nullptr) {
        this->ui->webView->setHtml("");
        return;
    }
    QFileInfo info("temp/" + editor->name() + ".html");
    this->_tempName = info.absoluteFilePath();
    this->ui->webView->setUrl(QUrl::fromLocalFile(this->_tempName));
}

QString Preview::getLineNumAnchor(int lineNum) const {
    return QString("__line__%1__").arg(lineNum);
}
