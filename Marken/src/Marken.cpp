#include <QFileDialog>
#include <QMessageBox>
#include <QFileInfo>
#include <QMimeData>
#include <QList>
#include <QKeyEvent>
#include <QCoreApplication>
#include <QApplicationStateChangeEvent>
#include <QUrl>
#include <QDialog>
#include <QHBoxLayout>
#include <QSettings>
#include "Editor.h"
#include "Preview.h"
#include "Setting.h"
#include "ColorSchemeForm.h"
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
    this->connect(this->ui->tabWidget, SIGNAL(openFile(QString)), this, SLOT(tryOpen(QString)));
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

void Marken::modificationChanged(bool) {
    for (int i = 0; i < this->ui->tabWidget->count(); ++i) {
        Editor* editor = dynamic_cast<Editor*>(this->ui->tabWidget->widget(i));
        if (editor->document()->isModified()) {
            this->ui->tabWidget->setTabText(i, "*" + editor->name());
        } else {
            this->ui->tabWidget->setTabText(i, editor->name());
        }
    }
}

void Marken::fileChanged(const QString &path) {
    this->_changeList.insert(path);
}

void Marken::scrollPreview(const QRect &, int) {
    Editor* editor = dynamic_cast<Editor*>(this->ui->tabWidget->currentWidget());
    if (editor != nullptr) {
        int lineNum = editor->firstVisibleLineNum();
        this->ui->preview->scrollToLine(lineNum);
    }
}

void Marken::on_actionNew_triggered() {
    Editor *editor = new Editor();
    this->ui->tabWidget->addTab(editor, editor->name());
    this->ui->tabWidget->setCurrentIndex(this->ui->tabWidget->count() - 1);
    this->connect(editor, SIGNAL(modificationChanged(bool)), this, SLOT(modificationChanged(bool)));
}

bool Marken::tryOpen(QString path) {
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
        this->connect(editor, SIGNAL(modificationChanged(bool)), this, SLOT(modificationChanged(bool)));
        this->ui->preview->showPreview(editor);
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
    this->ui->preview->showPreview(editor);
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
        this->modificationChanged(true);
    }
}

void Marken::on_actionClose_triggered() {
    int index = this->ui->tabWidget->currentIndex();
    if (index != -1) {
        Editor *editor = dynamic_cast<Editor*>(this->ui->tabWidget->widget(index));
        if (editor->document()->isModified()) {
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
        if (editor->document()->isModified()) {
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

bool Marken::event(QEvent *e) {
    if (e->type() == QEvent::WindowActivate) {
        auto temp = this->_changeList;
        this->_changeList.clear();
        for (auto path : temp) {
            for (int i = 0; i < this->ui->tabWidget->count(); ++i) {
                Editor* editor = dynamic_cast<Editor*>(this->ui->tabWidget->widget(i));
                if (editor->path() == path) {
                    this->ui->tabWidget->setCurrentIndex(i);
                    QString title = tr("Reload File");
                    QString text = tr("File is modified by other program, do you want to reload it?");
                    auto buttons = QMessageBox::Yes | QMessageBox::No;
                    auto defaultButton = QMessageBox::Yes;
                    auto result = QMessageBox::question(this, title, text, buttons, defaultButton);
                    if (result == QMessageBox::Yes) {
                        editor->loadText();
                    } else {
                        editor->document()->setModified(true);
                    }
                    break;
                }
            }
        }
    }
    return QMainWindow::event(e);
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
        QCoreApplication::postEvent(editor, event);
    }
}

void Marken::on_actionRedo_triggered() {
    int index = this->ui->tabWidget->currentIndex();
    if (index != -1) {
        QKeyEvent *event = new QKeyEvent(QEvent::KeyPress, Qt::Key_Y, Qt::ControlModifier);
        Editor* editor = dynamic_cast<Editor*>(this->ui->tabWidget->widget(index));
        QCoreApplication::postEvent(editor, event);
    }
}

void Marken::on_actionCut_triggered() {
    int index = this->ui->tabWidget->currentIndex();
    if (index != -1) {
        QKeyEvent *event = new QKeyEvent(QEvent::KeyPress, Qt::Key_X, Qt::ControlModifier);
        Editor* editor = dynamic_cast<Editor*>(this->ui->tabWidget->widget(index));
        QCoreApplication::postEvent(editor, event);
    }
}

void Marken::on_actionCopy_triggered() {
    int index = this->ui->tabWidget->currentIndex();
    if (index != -1) {
        QKeyEvent *event = new QKeyEvent(QEvent::KeyPress, Qt::Key_C, Qt::ControlModifier);
        Editor* editor = dynamic_cast<Editor*>(this->ui->tabWidget->widget(index));
        QCoreApplication::postEvent(editor, event);
    }
}

void Marken::on_actionPaste_triggered() {
    int index = this->ui->tabWidget->currentIndex();
    if (index != -1) {
        QKeyEvent *event = new QKeyEvent(QEvent::KeyPress, Qt::Key_V, Qt::ControlModifier);
        Editor* editor = dynamic_cast<Editor*>(this->ui->tabWidget->widget(index));
        QCoreApplication::postEvent(editor, event);
    }
}

void Marken::on_actionDelete_triggered() {
    int index = this->ui->tabWidget->currentIndex();
    if (index != -1) {
        QKeyEvent *event = new QKeyEvent(QEvent::KeyPress, Qt::Key_Delete, Qt::NoModifier);
        Editor* editor = dynamic_cast<Editor*>(this->ui->tabWidget->widget(index));
        QCoreApplication::postEvent(editor, event);
    }
}

void Marken::on_actionSelect_All_triggered() {
    int index = this->ui->tabWidget->currentIndex();
    if (index != -1) {
        QKeyEvent *event = new QKeyEvent(QEvent::KeyPress, Qt::Key_A, Qt::ControlModifier);
        Editor* editor = dynamic_cast<Editor*>(this->ui->tabWidget->widget(index));
        QCoreApplication::postEvent(editor, event);
    }
}

void Marken::on_actionPreference_triggered() {
     QDialog dialog(this);
     dialog.setLayout(new QHBoxLayout());
     dialog.layout()->addWidget(new ColorSchemeForm());
     dialog.exec();
     for (int i = 0; i < this->ui->tabWidget->count(); ++i) {
         Editor* editor = dynamic_cast<Editor*>(this->ui->tabWidget->widget(i));
         editor->updateColorScheme();
         editor->rehighlight();
     }
}

void Marken::on_actionAtx_Header_1_triggered() {
    Editor* editor = dynamic_cast<Editor*>(this->ui->tabWidget->currentWidget());
    editor->addAtxHeader(1);
}

void Marken::on_actionAtx_Header_2_triggered() {
    Editor* editor = dynamic_cast<Editor*>(this->ui->tabWidget->currentWidget());
    editor->addAtxHeader(2);
}

void Marken::on_actionAtx_Header_3_triggered() {
    Editor* editor = dynamic_cast<Editor*>(this->ui->tabWidget->currentWidget());
    editor->addAtxHeader(3);
}

void Marken::on_actionAtx_Header_4_triggered() {
    Editor* editor = dynamic_cast<Editor*>(this->ui->tabWidget->currentWidget());
    editor->addAtxHeader(4);
}

void Marken::on_actionAtx_Header_5_triggered() {
    Editor* editor = dynamic_cast<Editor*>(this->ui->tabWidget->currentWidget());
    editor->addAtxHeader(5);
}

void Marken::on_actionAtx_Header_6_triggered() {
    Editor* editor = dynamic_cast<Editor*>(this->ui->tabWidget->currentWidget());
    editor->addAtxHeader(6);
}

void Marken::on_actionSetext_Header_1_triggered() {
    Editor* editor = dynamic_cast<Editor*>(this->ui->tabWidget->currentWidget());
    editor->addSetextHeader(1);
}

void Marken::on_actionSetext_Header_2_triggered() {
    Editor* editor = dynamic_cast<Editor*>(this->ui->tabWidget->currentWidget());
    editor->addSetextHeader(2);
}

void Marken::on_actionHorizon_Line_triggered() {
    Editor* editor = dynamic_cast<Editor*>(this->ui->tabWidget->currentWidget());
    editor->addHorizonLine();
}

void Marken::on_actionInline_Link_triggered() {
    Editor* editor = dynamic_cast<Editor*>(this->ui->tabWidget->currentWidget());
    editor->addInlineLink();
}

void Marken::on_actionInline_Code_triggered() {
    Editor* editor = dynamic_cast<Editor*>(this->ui->tabWidget->currentWidget());
    editor->addInlineCode();
}

void Marken::on_actionImage_triggered() {
    Editor* editor = dynamic_cast<Editor*>(this->ui->tabWidget->currentWidget());
    editor->addInlineImage();
}

void Marken::on_actionReference_Link_triggered() {
    Editor* editor = dynamic_cast<Editor*>(this->ui->tabWidget->currentWidget());
    editor->addReferenceLink();
}

void Marken::on_actionOrdered_List_triggered() {
    Editor* editor = dynamic_cast<Editor*>(this->ui->tabWidget->currentWidget());
    editor->addOrderedList();
}

void Marken::on_actionUnordered_List_triggered() {
    Editor* editor = dynamic_cast<Editor*>(this->ui->tabWidget->currentWidget());
    editor->addUnorderedList();
}

void Marken::on_actionQuote_triggered() {
    Editor* editor = dynamic_cast<Editor*>(this->ui->tabWidget->currentWidget());
    editor->addQuote();
}

void Marken::on_actionUnquote_triggered() {
    Editor* editor = dynamic_cast<Editor*>(this->ui->tabWidget->currentWidget());
    editor->addUnquote();
}

void Marken::on_actionLink_Label_triggered() {
    Editor* editor = dynamic_cast<Editor*>(this->ui->tabWidget->currentWidget());
    editor->addLinkLabel();
}

void Marken::on_actionEmphasis_triggered() {
    Editor* editor = dynamic_cast<Editor*>(this->ui->tabWidget->currentWidget());
    editor->addEmphasis();
}

void Marken::on_actionBold_triggered() {
    Editor* editor = dynamic_cast<Editor*>(this->ui->tabWidget->currentWidget());
    editor->addBold();
}

void Marken::on_actionSyntax_Document_triggered() {
    this->tryOpen("doc/syntax.md");
}

void Marken::on_actionAbout_Marken_triggered() {
    this->tryOpen("doc/about.md");
}

void Marken::on_actionHTML_triggered() {
    int index = this->ui->tabWidget->currentIndex();
    if (index != -1) {
        Editor *editor = dynamic_cast<Editor*>(this->ui->tabWidget->widget(index));
        QString caption = tr("Save File");
        QString dir = "";
        QString filter = tr("HTML file(*.html);;All files(*.*)");
        QString path = QFileDialog::getSaveFileName(this, caption, dir, filter);
        if (!path.isEmpty()) {
            editor->saveAsHtml(path);
        }
    }
}

void Marken::on_tabWidget_currentChanged(int index) {
    this->disconnect(this, SLOT(scrollPreview(QRect, int)));
    if (index != -1) {
        Editor* editor = dynamic_cast<Editor*>(this->ui->tabWidget->widget(index));
        this->connect(editor, SIGNAL(updateRequest(QRect,int)), this, SLOT(scrollPreview(QRect,int)));
    }
}
