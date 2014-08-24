#include <ctime>
#include <cstdlib>
#include <QDir>
#include <QFile>
#include <QTextStream>
#include <QProcess>
#include <QUrl>
#include <QScrollBar>
#include <QTextCursor>
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
    this->_editor = editor;
    this->disconnect(this, SLOT(scroll(QRect, int)));
    if (editor != nullptr) {
        this->ui->textBrowser->setDocument(editor->parsedDocument());
        this->connect(editor, SIGNAL(updateRequest(QRect,int)), this, SLOT(scroll(QRect,int)));
    }
}

void Previewer::scroll(const QRect &, int) {
    this->_editor->scrollParsedDocument(this->ui->textBrowser);
}
