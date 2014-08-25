#include "MarkdownBlockData.h"
#include "MarkdownParser.h"
#include "Previewer.h"
#include "ui_Previewer.h"

Previewer::Previewer(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Previewer) {
    ui->setupUi(this);
}

Previewer::~Previewer() {
    delete ui;
}

void Previewer::showPreview(MarkdownEditor *editor) {
    MarkdownParser parser;
    QString html = parser.generateHtml(editor->document());
    this->ui->textBrowser->setHtml(html);
}

