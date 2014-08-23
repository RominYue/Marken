#include <ctime>
#include <cstdlib>
#include <QDir>
#include <QFile>
#include <QTextStream>
#include <QProcess>
#include <QUrl>
#include "MarkdownBlockData.h"
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
    QString html;
    QTextBlock block = editor->document()->firstBlock();
    while (block.isValid()) {
        MarkdownBlockData *data = dynamic_cast<MarkdownBlockData*>(block.userData());
        html += data->html();
        block = block.next();
    }
    this->ui->textEdit->setHtml(html);
}
