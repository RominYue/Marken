#include <ctime>
#include <cstdlib>
#include <QDir>
#include <QFile>
#include <QTextStream>
#include <QProcess>
#include <QUrl>
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
    QDir tempDir;
    if (!tempDir.exists("temp")) {
        tempDir.mkdir("temp");
    }
    srand(time(0));
    for (int i = 0; i < editor->path().length(); ++i) {
        for (int j = 0; j < editor->path().at(i); ++j) {
            rand();
        }
    }
    QString randomName = "temp/";
    for (int i = 0; i < 32; ++i) {
        int temp = rand() % 16;
        if (temp < 10) {
            randomName += '0' + temp;
        } else {
            randomName += 'A' + temp;
        }
    }
    QFile markdownFile(randomName + ".md");
    if (!markdownFile.open(QIODevice::WriteOnly | QIODevice::Text)) {
        return;
    }
    QTextStream out(&markdownFile);
    out.setCodec("UTF-8");
    out << editor->toPlainText() << endl;
    markdownFile.close();
    QProcess::execute("./mdc " + randomName + ".md " + randomName + ".html");
    QFile htmlFile(randomName + ".html");
    if (!htmlFile.open(QIODevice::ReadOnly | QIODevice::Text)) {
        return;
    }
    QTextStream in(&htmlFile);
    in.setCodec("UTF-8");
    this->ui->textEdit->setHtml(in.readAll());
    htmlFile.close();
}
