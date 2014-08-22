#include <QFileInfo>
#include <QFile>
#include <QTabWidget>
#include <QTextStream>
#include <QPalette>
#include "Setting.h"
#include "MarkdownHighlighter.h"
#include "Editor.h"
#include "ui_editor.h"

Editor::Editor(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Editor) {
    this->ui->setupUi(this);
    this->highlighter = new MarkdownHighlighter(this->ui->markdownEditor->document());
    this->_name = tr("New File");
    this->_path = "";
    this->updateColorScheme();
    this->_modified = false;
    this->_lastLength = 0;
    this->connect(this->ui->markdownEditor, SIGNAL(textChanged()), this, SLOT(on_markdownEditor_textChanged()));
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
        this->ui->markdownEditor->setPlainText(in.readAll());
        file.close();
        this->_modified = false;
    }
    this->_lastLength = this->ui->markdownEditor->toPlainText().length();
}

void Editor::save() {
    QFile file(this->_path);
    if (file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QTextStream out(&file);
        out.setCodec("UTF-8");
        out << this->ui->markdownEditor->toPlainText();
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

MarkdownEditor* Editor::editor() const {
    return this->ui->markdownEditor;
}

void Editor::updateColorScheme() {
    ColorSchemeSetting& scheme = Setting::instance()->colorScheme;
    ColorSchemeNode& node = scheme.scheme().color("Default");
    this->ui->markdownEditor->setFont(scheme.font());
    QPalette palette = this->ui->markdownEditor->palette();
    palette.setColor(QPalette::Base, node.background());
    this->ui->markdownEditor->setPalette(palette);
}

void Editor::rehighlight() {
    this->highlighter->rehighlight();
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

void Editor::on_markdownEditor_textChanged() {
    if (!this->_modified) {
        int newLength = this->ui->markdownEditor->toPlainText().length();
        if (this->_lastLength != newLength) {
            this->_modified = true;
            this->updateTitle();
            this->_lastLength = newLength;
        }
    }
}
