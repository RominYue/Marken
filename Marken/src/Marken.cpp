#include <QFileDialog>
#include <QMessageBox>
#include <QFileInfo>
#include <QMimeData>
#include <QList>
#include <QKeyEvent>
#include <QCoreApplication>
#include <QUrl>
#include <QDialog>
#include <QHBoxLayout>
#include <QSettings>
#include "ColorSchemeWidget.h"
#include "Setting.h"
#include "Editor.h"
#include "Previewer.h"
#include "Marken.h"
#include "ui_Marken.h"

Marken::Marken(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Marken) {
    this->ui->setupUi(this);
    this->initToolbar();
    this->on_actionNew_triggered();
    QSettings settings;
    restoreGeometry(settings.value("mainWindowGeometry").toByteArray());
    restoreState(settings.value("mainWindowState").toByteArray());
}

Marken::~Marken() {
    delete ui;
}

void Marken::initToolbar() {
    QToolBar *toolBarFile = addToolBar(tr("File"));
    toolBarFile->setObjectName("toolBarFile");
    toolBarFile->addAction(this->ui->actionNew);
    toolBarFile->addAction(this->ui->actionOpen);
    toolBarFile->addAction(this->ui->actionSave);
    toolBarFile->addAction(this->ui->actionSave_As);
    toolBarFile->addAction(this->ui->actionSave_All);
    QToolBar *toolBarEdit = addToolBar(tr("Edit"));
    toolBarEdit->setObjectName("toolBarEdit");
    toolBarEdit->addAction(this->ui->actionUndo);
    toolBarEdit->addAction(this->ui->actionRedo);
    toolBarEdit->addSeparator();
    toolBarEdit->addAction(this->ui->actionCopy);
    toolBarEdit->addAction(this->ui->actionPaste);
    toolBarEdit->addAction(this->ui->actionCut);
    QToolBar *toolBarTool = addToolBar(tr("Tool"));
    toolBarTool->setObjectName("toolBarTool");
    toolBarTool->addAction(this->ui->actionPreview);
}

void Marken::on_actionNew_triggered() {
    Editor *editor = new Editor();
    this->ui->tabWidget->addTab(editor, editor->name());
    this->ui->tabWidget->setCurrentIndex(this->ui->tabWidget->count() - 1);
}

bool Marken::tryOpen(const QString &path) {
    QFileInfo info(path);
    QString absolute = info.absoluteFilePath();
    bool flag = true;
    for (int i = 0; i < this->ui->tabWidget->count(); ++i) {
        Editor *editor = dynamic_cast<Editor*>(this->ui->tabWidget->widget(i));
        if (editor->path() == absolute) {
            flag = false;
            break;
        }
    }
    if (flag) {
        Editor *editor = new Editor();
        editor->open(path);
        this->ui->tabWidget->addTab(editor, editor->name());
        this->ui->tabWidget->setCurrentIndex(this->ui->tabWidget->count() - 1);
    }
    return true;
}

void Marken::on_actionOpen_triggered() {
    QString caption = tr("Open File");
    QString dir = "";
    QString filter = tr("Markdown file(*.md);;All files(*.*)");
    QStringList pathes = QFileDialog::getOpenFileNames(this, caption, dir, filter);
    for (auto path : pathes) {
        this->tryOpen(path);
    }
}

/**
 * @brief Try to save an editor.
 * @return true if saved successfully, otherwise false.
 */
bool Marken::trySave() {
    int index = this->ui->tabWidget->currentIndex();
    if (index == -1) {
        return false;
    }
    Editor *editor = dynamic_cast<Editor*>(this->ui->tabWidget->widget(index));
    if (editor->path().isEmpty()) {
        Editor *editor = dynamic_cast<Editor*>(this->ui->tabWidget->widget(index));
        QString caption = tr("Save File");
        QString dir = "";
        QString filter = tr("Markdown file(*.md);;All files(*.*)");
        QString path = QFileDialog::getSaveFileName(this, caption, dir, filter);
        if (path.isEmpty()) {
            return false;
        }
        editor->setPath(path);
    }
    editor->save();
    return true;
}

void Marken::on_actionSave_triggered() {
    this->trySave();
}

void Marken::on_actionSave_All_triggered() {
    for (int i = 0; i < this->ui->tabWidget->count(); ++i) {
        this->ui->tabWidget->setCurrentIndex(i);
        if (!this->trySave()) {
            break;
        }
    }
}

void Marken::on_actionSave_As_triggered() {
    int index = this->ui->tabWidget->currentIndex();
    if (index != -1) {
        Editor *editor = dynamic_cast<Editor*>(this->ui->tabWidget->widget(index));
        QString caption = tr("Save File");
        QString dir = "";
        QString filter = tr("Markdown file(*.md);;All files(*.*)");
        QString path = QFileDialog::getSaveFileName(this, caption, dir, filter);
        if (!path.isEmpty()) {
            editor->saveAs(path);
        }
    }
}

void Marken::on_actionClose_triggered() {
    int index = this->ui->tabWidget->currentIndex();
    if (index != -1) {
        Editor *editor = dynamic_cast<Editor*>(this->ui->tabWidget->widget(index));
        if (editor->isModified()) {
            QString title = tr("Save File");
            QString text = tr("Save %1 before closed?").arg(editor->name());
            auto buttons = QMessageBox::Yes | QMessageBox::No | QMessageBox::Cancel;
            auto defaultButton = QMessageBox::Yes;
            auto result = QMessageBox::question(this, title, text, buttons, defaultButton);
            switch (result) {
            case QMessageBox::Yes:
                editor->save();
                this->ui->tabWidget->removeTab(index);
                break;
            case QMessageBox::No:
                this->ui->tabWidget->removeTab(index);
                break;
            case QMessageBox::Cancel:
                break;
            default:
                break;
            }
        } else {
            this->ui->tabWidget->removeTab(index);
        }
    }
    if (this->ui->tabWidget->count() == 0) {
        this->on_actionNew_triggered();
    }
}

/**
 * @brief Try to close all the tabs in tab widget.
 * @return false if cancel is pressed, otherwise true.
 */
bool Marken::tryCloseAll() {
    bool saveAll = false;
    bool ignoreAll = false;
    for (int i = this->ui->tabWidget->count() - 1; i >= 0; --i) {
        this->ui->tabWidget->setCurrentIndex(i);
        Editor *editor = dynamic_cast<Editor*>(this->ui->tabWidget->widget(i));
        if (editor->isModified()) {
            if (saveAll) {
                if (!this->trySave()) {
                    return false;
                }
            } else if (!ignoreAll) {
                QString title = tr("Save File");
                QString text = tr("File is modified, save file?");
                auto buttons = QMessageBox::Yes | QMessageBox::No |
                        QMessageBox::YesToAll | QMessageBox::NoToAll |
                        QMessageBox::Cancel;
                auto defaultButton = QMessageBox::Yes;
                auto result = QMessageBox::question(this, title, text, buttons, defaultButton);
                switch (result) {
                case QMessageBox::Yes:
                    if (!this->trySave()) {
                        return false;
                    }
                    break;
                case QMessageBox::No:
                    break;
                case QMessageBox::YesToAll:
                    saveAll = true;
                    if (!this->trySave()) {
                        return false;
                    }
                    break;
                case QMessageBox::NoToAll:
                    ignoreAll = true;
                    break;
                case QMessageBox::Cancel:
                    return false;
                default:
                    break;
                }
            }
        }
        this->ui->tabWidget->removeTab(i);
    }
    this->on_actionNew_triggered();
    return true;
}

void Marken::on_actionClose_All_triggered() {
    this->tryCloseAll();
}

void Marken::on_actionQuit_triggered() {
    this->close();
}

void Marken::closeEvent(QCloseEvent *event) {
    if (this->tryCloseAll()) {
        QSettings settings;
        settings.setValue("mainWindowGeometry", saveGeometry());
        settings.setValue("mainWindowState", saveState());
        event->accept();
    } else {
        event->ignore();
    }
}

void Marken::on_tabWidget_tabCloseRequested(int index) {
    this->ui->tabWidget->setCurrentIndex(index);
    this->on_actionClose_triggered();
}

void Marken::on_actionUndo_triggered() {
    int index = this->ui->tabWidget->currentIndex();
    if (index != -1) {
        QKeyEvent *event = new QKeyEvent(QEvent::KeyPress, Qt::Key_Z, Qt::ControlModifier);
        Editor* editor = dynamic_cast<Editor*>(this->ui->tabWidget->widget(index));
        QCoreApplication::postEvent(editor->editor(), event);
    }
}

void Marken::on_actionRedo_triggered() {
    int index = this->ui->tabWidget->currentIndex();
    if (index != -1) {
        QKeyEvent *event = new QKeyEvent(QEvent::KeyPress, Qt::Key_Y, Qt::ControlModifier);
        Editor* editor = dynamic_cast<Editor*>(this->ui->tabWidget->widget(index));
        QCoreApplication::postEvent(editor->editor(), event);
    }
}

void Marken::on_actionCut_triggered() {
    int index = this->ui->tabWidget->currentIndex();
    if (index != -1) {
        QKeyEvent *event = new QKeyEvent(QEvent::KeyPress, Qt::Key_X, Qt::ControlModifier);
        Editor* editor = dynamic_cast<Editor*>(this->ui->tabWidget->widget(index));
        QCoreApplication::postEvent(editor->editor(), event);
    }
}

void Marken::on_actionCopy_triggered() {
    int index = this->ui->tabWidget->currentIndex();
    if (index != -1) {
        QKeyEvent *event = new QKeyEvent(QEvent::KeyPress, Qt::Key_C, Qt::ControlModifier);
        Editor* editor = dynamic_cast<Editor*>(this->ui->tabWidget->widget(index));
        QCoreApplication::postEvent(editor->editor(), event);
    }
}

void Marken::on_actionPaste_triggered() {
    int index = this->ui->tabWidget->currentIndex();
    if (index != -1) {
        QKeyEvent *event = new QKeyEvent(QEvent::KeyPress, Qt::Key_V, Qt::ControlModifier);
        Editor* editor = dynamic_cast<Editor*>(this->ui->tabWidget->widget(index));
        QCoreApplication::postEvent(editor->editor(), event);
    }
}

void Marken::on_actionDelete_triggered() {
    int index = this->ui->tabWidget->currentIndex();
    if (index != -1) {
        QKeyEvent *event = new QKeyEvent(QEvent::KeyPress, Qt::Key_Delete, Qt::NoModifier);
        Editor* editor = dynamic_cast<Editor*>(this->ui->tabWidget->widget(index));
        QCoreApplication::postEvent(editor->editor(), event);
    }
}

void Marken::on_actionSelect_All_triggered() {
    int index = this->ui->tabWidget->currentIndex();
    if (index != -1) {
        QKeyEvent *event = new QKeyEvent(QEvent::KeyPress, Qt::Key_A, Qt::ControlModifier);
        Editor* editor = dynamic_cast<Editor*>(this->ui->tabWidget->widget(index));
        QCoreApplication::postEvent(editor->editor(), event);
    }
}

void Marken::on_actionPreference_triggered() {
    QDialog dialog;
    dialog.setLayout(new QHBoxLayout());
    dialog.layout()->addWidget(new ColorSchemeWidget());
    dialog.exec();
    Setting::instance()->colorScheme.save();
    for (int i = 0; i < this->ui->tabWidget->count(); ++i) {
        Editor* editor = dynamic_cast<Editor*>(this->ui->tabWidget->widget(i));
        editor->updateColorScheme();
        editor->rehighlight();
    }
}

void Marken::on_actionPreview_triggered() {
    Editor* editor = dynamic_cast<Editor*>(this->ui->tabWidget->currentWidget());
    this->ui->previewer->showPreview(editor);
}

void Marken::on_actionSyntax_triggered() {
    this->tryOpen("doc/parse.md");
}
