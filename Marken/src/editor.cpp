#include <QFileInfo>
#include <QFile>
#include <QTabWidget>
#include <QTextStream>
#include "markdownhighlighter.h"
#include "editor.h"
#include "ui_editor.h"

Editor::Editor(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Editor) {
    this->ui->setupUi(this);
    this->_name = tr("New File");
    this->_path = "";
    this->_modified = false;
    new MarkdownHighlighter(this->ui->textEdit->document());
}

Editor::~Editor() {
    delete ui;
}

QString Editor::name() const {
    return this->_name;
}

QString Editor::path() const {
    return this->_path;
}

bool Editor::isModified() const {
    return this->_modified;
}

void Editor::setPath(const QString &path) {
    QFileInfo info(path);
    this->_path = info.absoluteFilePath();
    this->_name = info.fileName();
}

void Editor::open(const QString &path) {
    this->setPath(path);
    QFile file(path);
    if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QTextStream in(&file);
        in.setCodec("UTF-8");
        this->ui->textEdit->setText(in.readAll());
        file.close();
        this->_modified = false;
    }
}

void Editor::save() {
    QFile file(this->_path);
    if (file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QTextStream out(&file);
        out.setCodec("UTF-8");
        out << this->ui->textEdit->toPlainText();
        out.flush();
        file.close();
        if (this->_modified) {
            this->_modified = false;
            this->updateTitle();
        }
    }
}

void Editor::saveAs(const QString &path) {
    this->setPath(path);
    this->save();
}

void Editor::updateTitle() {
    QString title = this->_name;
    if (this->_modified) {
        title = "*" + title;
    }
    if (this->parent() != nullptr) {
        QWidget *stack = dynamic_cast<QWidget*>(this->parent());
        if (stack != nullptr) {
            QTabWidget *tab = dynamic_cast<QTabWidget*>(stack->parent());
            if (tab != nullptr) {
                for (int i = 0; i < tab->count(); ++i) {
                    if (this == dynamic_cast<Editor*>(tab->widget(i))) {
                        tab->setTabText(i, title);
                    }
                }
            }
        }
    }
}

void Editor::on_textEdit_textChanged() {
    if (not this->_modified) {
        this->_modified = true;
        this->updateTitle();
    }
}

