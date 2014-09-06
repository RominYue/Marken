#include <QPainter>
#include <QTextBlock>
#include <QFileInfo>
#include <QFile>
#include <QTextStream>
#include <QPalette>
#include "parse_line.h"
#include "BlockData.h"
#include "LineNumberArea.h"
#include "Highlighter.h"
#include "Setting.h"
#include "Editor.h"

Editor::Editor(QWidget *parent) :
    QPlainTextEdit(parent) {
    this->_name = tr("New File");
    this->_path = "";

    this->_lineNumberArea = new LineNumberArea(this);
    this->connect(this, SIGNAL(blockCountChanged(int)), this, SLOT(updateLineNumberAreaWidth(int)));
    this->connect(this, SIGNAL(updateRequest(QRect,int)), this, SLOT(updateLineNumberArea(QRect,int)));
    this->updateLineNumberAreaWidth(0);

    this->updateColorScheme();
    this->_parser = QSharedPointer<DynamicParser>(new DynamicParser());
    this->_highlighter = new Highlighter(this->document());
    this->_highlighter->setParser(this->_parser);
}

QString Editor::name() const {
    return this->_name;
}

QString Editor::path() const {
    return this->_path;
}

QSharedPointer<DynamicParser> Editor::parser() const {
    return this->_parser;
}

void Editor::setPath(const QString &path) {
    QFileInfo info(path);
    this->_path = info.absoluteFilePath();
    this->_name = info.fileName();
}

void Editor::open(const QString &path) {
    this->setPath(path);
    this->loadText();
}

void Editor::loadText() {
    QFile file(this->_path);
    if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QTextStream in(&file);
        in.setCodec("UTF-8");
        QString text = in.readAll();
        this->setPlainText(text);
        file.close();
        this->document()->setModified(false);
    }
}

void Editor::save() {
    QFile file(this->_path);
    if (file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QTextStream out(&file);
        out.setCodec("UTF-8");
        out << this->toPlainText();
        out.flush();
        file.close();
        this->document()->setModified(false);
    }
}

void Editor::saveAs(const QString &path) {
    this->setPath(path);
    this->save();
}

void Editor::saveAsHtml(const QString &path) {
    QFile file(path);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        return;
    }
    QString html;
    QTextBlock block = this->document()->firstBlock();
    while (block.isValid()) {
        html += QString::fromUtf8(dynamic_cast<BlockData*>(block.userData())->data()->generateHtml().c_str()) + "\n";
        block = block.next();
    }
    QTextStream fout(&file);
    fout.setCodec("UTF-8");
    fout << html;
    file.close();
}

void Editor::rehighlight() {
     this->_highlighter->rehighlight();
}

void Editor::updateColorScheme() {
    ColorSchemeSetting& setting = Setting::instance()->colorSetting;
    ColorScheme& scheme = setting.colorScheme();
    QFont font;
    font.setFamily(scheme.fontFamily());
    font.setPointSize(scheme.fontSize());
    font.setBold(scheme.bold(ParseElementType::TYPE_PARAGRAPH));
    font.setItalic(scheme.italic(ParseElementType::TYPE_PARAGRAPH));
    font.setUnderline(scheme.underline(ParseElementType::TYPE_PARAGRAPH));
    font.setStrikeOut(scheme.strikeout(ParseElementType::TYPE_PARAGRAPH));
    this->setFont(font);
    QPalette palette = this->palette();
    palette.setColor(QPalette::Base, scheme.background(ParseElementType::TYPE_PARAGRAPH));
    palette.setColor(QPalette::Text, scheme.foreground(ParseElementType::TYPE_PARAGRAPH));
    this->setPalette(palette);
}

int Editor::firstVisibleLineNum() const {
    return this->firstVisibleBlock().blockNumber() + 1;
}

int Editor::lineNumberAreaWidth() {
    int cnt = 0;
    int temp = this->blockCount() > 0 ? this->blockCount() : 1;
    while (temp) {
        temp /= 10;
        ++cnt;
    }
    int width = 10 + this->fontMetrics().width(QLatin1Char('9')) * cnt;
    if (width < 30) {
        width = 30;
    }
    return width;
}

void Editor::keyPressEvent(QKeyEvent *e) {
    if (e->key() == Qt::Key_Tab) {
        QTextCursor cursor = this->textCursor();
        if (cursor.hasSelection()) {
            this->multilineIndent(true);
        } else {
            this->spaceIndent();
        }
        return;
    }
    if (e->key() == Qt::Key_Backtab) {
        this->multilineIndent(false);
        return;
    }
    if (e->key() == Qt::Key_Return || e->key() == Qt::Key_Enter) {
        this->autoIndent();
        return;
    }
    QPlainTextEdit::keyPressEvent(e);
}

void Editor::spaceIndent() {
    QTextCursor cursor = this->textCursor();
    cursor.beginEditBlock();
    cursor.insertText("    ");
    cursor.endEditBlock();
}

void Editor::multilineIndent(bool increase) {
    QTextCursor cursor = this->textCursor();
    int spos = cursor.anchor();
    int epos = cursor.position();
    if (spos > epos) {
        int temp = spos;
        spos = epos;
        epos = temp;
    }
    cursor.setPosition(spos, QTextCursor::MoveAnchor);
    int sblock = cursor.block().blockNumber();
    cursor.setPosition(epos, QTextCursor::MoveAnchor);
    int eblock = cursor.block().blockNumber();
    cursor.setPosition(spos, QTextCursor::MoveAnchor);
    cursor.beginEditBlock();
    for (int i = 0; i <= (eblock - sblock); ++i) {
        cursor.movePosition(QTextCursor::StartOfBlock, QTextCursor::MoveAnchor);
        if (increase) {
            cursor.insertText("    ");
        } else {
            int pos = cursor.position();
            for (int i = 0; i < 4; ++i) {
                QChar next = this->toPlainText().at(pos);
                if (next == ' ') {
                    cursor.deleteChar();
                } else {
                    break;
                }
            }
        }
        cursor.movePosition(QTextCursor::NextBlock, QTextCursor::MoveAnchor);
    }
    cursor.endEditBlock();
    cursor.setPosition(spos, QTextCursor::MoveAnchor);
    cursor.movePosition(QTextCursor::StartOfBlock, QTextCursor::MoveAnchor);
    while (cursor.block().blockNumber() < eblock) {
        cursor.movePosition(QTextCursor::NextBlock, QTextCursor::KeepAnchor);
    }
    cursor.movePosition(QTextCursor::EndOfBlock, QTextCursor::KeepAnchor);
    this->setTextCursor(cursor);
}

void Editor::autoIndent() {
    QTextCursor cursor = this->textCursor();
    QString text = cursor.block().text();
    QString indent;
    bool nest = false;
    for (int i = 0; i <= text.size(); ++i) {
        if (i == text.size()) {
            indent = text;
            break;
        }
        if (text[i] == ' ' || text[i] == '\t' || text[i] == '>') {
            continue;
        } else if (text[i] == '*' || text[i] == '+' || text[i] == '-') {
            if (nest) {
                indent = text.left(i);
                break;
            } else {
                nest = true;
            }
        } else if (text[i] >= '0' && text[i] <= '9') {
            int num = 0, space = 0;
            for (int j = i; j < text.size(); ++j) {
                if (text[j] >= '0' && text[j] <= '9') {
                    num = num * 10 + text[j].toLatin1() - '0';
                } else if (text[j] == '.') {
                    for (int k = j + 1; k < text.size(); ++k) {
                        if (text[k] == ' ' || text[k] == '\t') {
                            ++space;
                        } else {
                            break;
                        }
                    }
                    break;
                } else {
                    num = -1;
                    break;
                }
            }
            if (num >= 0) {
                indent = text.left(i) + QString("%1.").arg(num + 1);
                for (int k = 0; k < space; ++k) {
                    indent += " ";
                }
            } else {
                indent = text.left(i);
            }
            break;
        } else {
            indent = text.left(i);
            break;
        }
    }
    cursor.beginEditBlock();
    cursor.insertText("\n" + indent);
    cursor.endEditBlock();
    this->setTextCursor(cursor);
}

void Editor::addAtxHeader(int num) {
    QTextCursor cursor = this->textCursor();
    cursor.beginEditBlock();
    if (cursor.hasSelection()) {
        cursor.removeSelectedText();
    }
    for (int i = 0; i < num; ++i) {
        cursor.insertText("#");
    }
    cursor.insertText(" ");
    cursor.endEditBlock();
    this->setTextCursor(cursor);
}

void Editor::addSetextHeader(int num) {
    QTextCursor cursor = this->textCursor();
    cursor.beginEditBlock();
    if (cursor.hasSelection()) {
        cursor.removeSelectedText();
    }
    cursor.insertBlock();
    cursor.movePosition(QTextCursor::NextBlock, QTextCursor::MoveAnchor);
    if (num == 1) {
        cursor.insertText("======");
    } else {
        cursor.insertText("-----");
    }
    cursor.movePosition(QTextCursor::PreviousBlock, QTextCursor::MoveAnchor);
    cursor.movePosition(QTextCursor::EndOfBlock, QTextCursor::MoveAnchor);
    cursor.endEditBlock();
    this->setTextCursor(cursor);
}

void Editor::addHorizonLine() {
    QTextCursor cursor = this->textCursor();
    cursor.beginEditBlock();
    if (cursor.hasSelection()) {
        cursor.removeSelectedText();
    }
    cursor.insertText("________");
    cursor.insertBlock();
    cursor.movePosition(QTextCursor::NextBlock, QTextCursor::MoveAnchor);
    cursor.endEditBlock();
    this->setTextCursor(cursor);
}

void Editor::addInlineLink() {
    QTextCursor cursor = this->textCursor();
    cursor.beginEditBlock();
    if (cursor.hasSelection()) {
        cursor.removeSelectedText();
    }
    cursor.insertText("[Text](Link)");
    cursor.endEditBlock();
    this->setTextCursor(cursor);
}

void Editor::addInlineCode() {
    QTextCursor cursor = this->textCursor();
    QString content;
    cursor.beginEditBlock();
    if (cursor.hasSelection()) {
        content = cursor.selectedText();
        cursor.removeSelectedText();
    }
    cursor.insertText("`" + content + "`");
    cursor.endEditBlock();
    this->setTextCursor(cursor);
}

void Editor::addInlineImage() {
    QTextCursor cursor = this->textCursor();
    cursor.beginEditBlock();
    if (cursor.hasSelection()) {
        cursor.removeSelectedText();
    }
    cursor.insertText("![Alt](Link)");
    cursor.endEditBlock();
    this->setTextCursor(cursor);
}

void Editor::addReferenceLink() {
    QTextCursor cursor = this->textCursor();
    cursor.beginEditBlock();
    if (cursor.hasSelection()) {
        cursor.removeSelectedText();
    }
    cursor.insertText("[Cite][Link]");
    cursor.endEditBlock();
    this->setTextCursor(cursor);
}

void Editor::addOrderedList() {
    this->multilineList(true);
}

void Editor::addUnorderedList() {
    this->multilineList(false);
}

void Editor::multilineList(bool ordered) {
    QTextCursor cursor = this->textCursor();
    int spos = cursor.anchor();
    int epos = cursor.position();
    if (spos > epos) {
        int temp = spos;
        spos = epos;
        epos = temp;
    }
    cursor.setPosition(spos, QTextCursor::MoveAnchor);
    int sblock = cursor.block().blockNumber();
    cursor.setPosition(epos, QTextCursor::MoveAnchor);
    int eblock = cursor.block().blockNumber();
    cursor.setPosition(spos, QTextCursor::MoveAnchor);
    cursor.beginEditBlock();
    for (int i = 0; i <= (eblock - sblock); ++i) {
        cursor.movePosition(QTextCursor::StartOfBlock, QTextCursor::MoveAnchor);
        if (ordered) {
            cursor.insertText(QString("%1. ").arg(i + 1));
        } else {
            cursor.insertText("* ");
        }
        cursor.movePosition(QTextCursor::NextBlock, QTextCursor::MoveAnchor);
    }
    cursor.endEditBlock();
    cursor.setPosition(spos, QTextCursor::MoveAnchor);
    cursor.movePosition(QTextCursor::StartOfBlock, QTextCursor::MoveAnchor);
    while (cursor.block().blockNumber() < eblock) {
        cursor.movePosition(QTextCursor::NextBlock, QTextCursor::KeepAnchor);
    }
    cursor.movePosition(QTextCursor::EndOfBlock, QTextCursor::KeepAnchor);
    this->setTextCursor(cursor);
}

void Editor::addQuote() {
    this->multilineQuote(true);
}

void Editor::addUnquote() {
    this->multilineQuote(false);
}

void Editor::multilineQuote(bool increase) {
    QTextCursor cursor = this->textCursor();
    int spos = cursor.anchor();
    int epos = cursor.position();
    if (spos > epos) {
        int temp = spos;
        spos = epos;
        epos = temp;
    }
    cursor.setPosition(spos, QTextCursor::MoveAnchor);
    int sblock = cursor.block().blockNumber();
    cursor.setPosition(epos, QTextCursor::MoveAnchor);
    int eblock = cursor.block().blockNumber();
    cursor.setPosition(spos, QTextCursor::MoveAnchor);
    cursor.beginEditBlock();
    for (int i = 0; i <= (eblock - sblock); ++i) {
        cursor.movePosition(QTextCursor::StartOfBlock, QTextCursor::MoveAnchor);
        if (increase) {
            cursor.insertText("> ");
        } else {
            int pos = cursor.position();
            QChar next = this->toPlainText().at(pos);
            if (next == '>') {
                cursor.deleteChar();
                next = this->toPlainText().at(pos);
                if (next == ' ') {
                    cursor.deleteChar();
                }
            }
        }
        cursor.movePosition(QTextCursor::NextBlock, QTextCursor::MoveAnchor);
    }
    cursor.endEditBlock();
    cursor.setPosition(spos, QTextCursor::MoveAnchor);
    cursor.movePosition(QTextCursor::StartOfBlock, QTextCursor::MoveAnchor);
    while (cursor.block().blockNumber() < eblock) {
        cursor.movePosition(QTextCursor::NextBlock, QTextCursor::KeepAnchor);
    }
    cursor.movePosition(QTextCursor::EndOfBlock, QTextCursor::KeepAnchor);
    this->setTextCursor(cursor);
}

void Editor::addLinkLabel() {
    QTextCursor cursor = this->textCursor();
    cursor.beginEditBlock();
    if (cursor.hasSelection()) {
        cursor.removeSelectedText();
    }
    cursor.insertText("[Cite]:(Link)");
    cursor.endEditBlock();
    this->setTextCursor(cursor);
}

void Editor::addEmphasis() {
    QTextCursor cursor = this->textCursor();
    QString content;
    cursor.beginEditBlock();
    bool insert = true;
    if (cursor.hasSelection()) {
        content = cursor.selectedText();
        if (content.size() >= 2) {
            if (content.left(1) == "*" && content.right(1) == "*") {
                insert = false;
            }
            if (content.left(1) == "_" && content.right(1) == "_") {
                insert = false;
            }
        }
    }
    if (insert) {
        cursor.insertText("_" + content + "_");
    } else {
        cursor.removeSelectedText();
        cursor.insertText(content.mid(1, content.size() - 2));
    }
    cursor.endEditBlock();
    this->setTextCursor(cursor);
}

void Editor::addBold() {
    QTextCursor cursor = this->textCursor();
    QString content;
    cursor.beginEditBlock();
    bool insert = true;
    if (cursor.hasSelection()) {
        content = cursor.selectedText();
        if (content.size() >= 4) {
            if (content.left(2) == "**" && content.right(2) == "**") {
                insert = false;
            }
            if (content.left(2) == "__" && content.right(2) == "__") {
                insert = false;
            }
        }
    }
    if (insert) {
        cursor.insertText("**" + content + "**");
    } else {
        cursor.removeSelectedText();
        cursor.insertText(content.mid(2, content.size() - 4));
    }
    cursor.endEditBlock();
    this->setTextCursor(cursor);
}

void Editor::updateLineNumberAreaWidth(int) {
    this->setViewportMargins(lineNumberAreaWidth(), 0, 0, 0);
}

void Editor::updateLineNumberArea(const QRect &rect, int dy) {
    if (dy) {
        this->_lineNumberArea->scroll(0, dy);
    } else {
        this->_lineNumberArea->update(0, rect.y(), this->_lineNumberArea->width(), rect.height());
    }
    if (rect.contains(this->viewport()->rect())) {
        this->updateLineNumberAreaWidth(0);
    }
}

void Editor::resizeEvent(QResizeEvent *e) {
    QPlainTextEdit::resizeEvent(e);
    QRect cr = contentsRect();
    this->_lineNumberArea->setGeometry(QRect(cr.left(), cr.top(), lineNumberAreaWidth(), cr.height()));
}

void Editor::lineNumberAreaPaintEvent(QPaintEvent *event) {
    QPainter painter(this->_lineNumberArea);
    painter.fillRect(event->rect(), Qt::lightGray);
    QTextBlock block = this->firstVisibleBlock();
    int blockNumber = block.blockNumber();
    int top = (int) blockBoundingGeometry(block).translated(contentOffset()).top();
    int bottom = top + (int) blockBoundingRect(block).height();
    while (block.isValid() && top <= event->rect().bottom()) {
        if (block.isVisible() && bottom >= event->rect().top()) {
            QString number = QString::number(blockNumber + 1);
            painter.setPen(Qt::black);
            painter.drawText(0, top, this->_lineNumberArea->width() - 5, fontMetrics().height(),
                             Qt::AlignRight, number);
        }
        block = block.next();
        top = bottom;
        bottom = top + (int) blockBoundingRect(block).height();
        ++blockNumber;
    }
}
