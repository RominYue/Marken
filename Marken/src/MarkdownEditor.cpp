#include <QPainter>
#include <QTextBlock>
#include <QFileInfo>
#include <QFile>
#include <QTextStream>
#include <QPalette>
#include "Setting.h"
#include "MarkdownEditor.h"

MarkdownEditor::MarkdownEditor(QWidget *parent) :
    QPlainTextEdit(parent) {
    this->_name = tr("New File");
    this->_path = "";

    this->_lineNumberArea = new LineNumberArea(this);
    this->connect(this, SIGNAL(blockCountChanged(int)), this, SLOT(updateLineNumberAreaWidth(int)));
    this->connect(this, SIGNAL(updateRequest(QRect,int)), this, SLOT(updateLineNumberArea(QRect,int)));
    this->connect(this, SIGNAL(cursorPositionChanged()), this, SLOT(highlightCurrentLine()));
    this->updateLineNumberAreaWidth(0);

    this->_highlighter = new MarkdownHighlighter(this->document());
    this->updateColorScheme();
    this->highlightCurrentLine();

    this->_parsedDocument = new QTextDocument(this);
    this->connect(this->_highlighter, SIGNAL(parseBlock(int)), this, SLOT(parseBlock(int)));
    this->_blockNums.append(1);
}

QString MarkdownEditor::name() const {
    return this->_name;
}

QString MarkdownEditor::path() const {
    return this->_path;
}

void MarkdownEditor::setPath(const QString &path) {
    QFileInfo info(path);
    this->_path = info.absoluteFilePath();
    this->_name = info.fileName();
}

void MarkdownEditor::open(const QString &path) {
    this->setPath(path);
    QFile file(path);
    if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QTextStream in(&file);
        in.setCodec("UTF-8");
        this->setPlainText(in.readAll());
        file.close();
        this->document()->setModified(false);
    }
}

void MarkdownEditor::save() {
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

void MarkdownEditor::saveAs(const QString &path) {
    this->setPath(path);
    this->save();
}

void MarkdownEditor::updateColorScheme() {
    ColorSchemeSetting& scheme = Setting::instance()->colorScheme;
    ColorSchemeNode& node = scheme.scheme().color();
    this->setFont(scheme.font());
    QPalette palette = this->palette();
    palette.setColor(QPalette::Base, node.background());
    palette.setColor(QPalette::Text, node.foreground());
    this->setPalette(palette);
}

void MarkdownEditor::rehighlight() {
    this->_highlighter->rehighlight();
    this->highlightCurrentLine();
}

int MarkdownEditor::lineNumberAreaWidth() {
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

void MarkdownEditor::keyPressEvent(QKeyEvent *e) {
    if (e->key() == Qt::Key_Tab) {
        QTextCursor cursor = this->textCursor();
        if (cursor.hasSelection()) {
            if (e->modifiers() == Qt::NoModifier) {
                this->multilineIndent(true);
                return;
            } else if (e->modifiers() & Qt::ShiftModifier) {
                this->multilineIndent(false);
                return;
            }
        } else if (e->modifiers() & Qt::NoModifier) {
            this->spaceIndent();
            return;
        }
    } else if (e->key() == Qt::Key_Return && (e->modifiers() & Qt::NoModifier)) {
        this->autoIndent();
        //return;
    }
    QPlainTextEdit::keyPressEvent(e);
}

void MarkdownEditor::spaceIndent() {
    QTextCursor cursor = this->textCursor();
    cursor.beginEditBlock();
    cursor.insertText("    ");
    cursor.endEditBlock();
}

void MarkdownEditor::multilineIndent(bool increase) {
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
                QChar next = this->toPlainText().at(pos + 1);
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

void MarkdownEditor::autoIndent() {
    QTextCursor cursor = this->textCursor();
    // TODO
}

void MarkdownEditor::addAtxHeader(int num) {
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

void MarkdownEditor::addSetextHeader(int num) {
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

void MarkdownEditor::addHorizonLine() {
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

QTextDocument* MarkdownEditor::parsedDocument() const {
    return this->_parsedDocument;
}

void MarkdownEditor::updateLineNumberAreaWidth(int) {
    this->setViewportMargins(lineNumberAreaWidth(), 0, 0, 0);
}

void MarkdownEditor::updateLineNumberArea(const QRect &rect, int dy) {
    if (dy) {
        this->_lineNumberArea->scroll(0, dy);
    } else {
        this->_lineNumberArea->update(0, rect.y(), this->_lineNumberArea->width(), rect.height());
    }
    if (rect.contains(this->viewport()->rect())) {
        this->updateLineNumberAreaWidth(0);
    }
}

void MarkdownEditor::highlightCurrentLine() {
    QList<QTextEdit::ExtraSelection> extraSelections;
    if (!isReadOnly()) {
        QTextEdit::ExtraSelection selection;
        QColor lineColor;
        if (this->palette().base().color().value() < 128) {
            lineColor = this->palette().base().color().lighter();
        } else {
            lineColor = this->palette().base().color().darker();
        }
        selection.format.setBackground(lineColor);
        selection.format.setProperty(QTextFormat::FullWidthSelection, true);
        selection.cursor = textCursor();
        selection.cursor.clearSelection();
        extraSelections.append(selection);
    }
    setExtraSelections(extraSelections);
}

void MarkdownEditor::resizeEvent(QResizeEvent *e) {
    QPlainTextEdit::resizeEvent(e);
    QRect cr = contentsRect();
    this->_lineNumberArea->setGeometry(QRect(cr.left(), cr.top(), lineNumberAreaWidth(), cr.height()));
}

void MarkdownEditor::lineNumberAreaPaintEvent(QPaintEvent *event) {
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

int MarkdownEditor::getParsedBlockNum() const {
    int num = 0;
    for (int i = 0; i < this->_blockNums.size(); ++i) {
        if (this->_blockNums[i] > 0) {
            ++num;
        }
    }
    return num;
}

QTextBlock MarkdownEditor::findParsedBlock(int blockNum) const {
    int parsedBlockNum = 0;
    for (int i = 0; i < blockNum; ++i) {
        parsedBlockNum += this->_blockNums[parsedBlockNum];
    }
    return this->_parsedDocument->findBlockByNumber(parsedBlockNum);
}

QTextBlock MarkdownEditor::findParsedLastBlock(int blockNum) const {
    QTextBlock block = this->findParsedBlock(blockNum);
    int num = this->_blockNums[block.blockNumber()];
    for (int i = 1; i < num; ++i) {
        block = block.next();
    }
    return block;
}

int MarkdownEditor::countParsedBlock(int blockCnt, int index) const {
    int cnt = 0;
    for (int i = 0; i < blockCnt; ++i) {
        cnt += this->_blockNums[index + cnt];
    }
    return cnt;
}

void MarkdownEditor::scrollParsedDocument(QTextEdit *textEdit) {
    int blockNum = this->firstVisibleBlock().blockNumber();
    QTextCursor lastCursor(this->_parsedDocument->lastBlock());
    lastCursor.movePosition(QTextCursor::EndOfBlock, QTextCursor::MoveAnchor);
    textEdit->setTextCursor(lastCursor);
    QTextCursor cursor(this->findParsedBlock(blockNum));
    cursor.movePosition(QTextCursor::StartOfBlock, QTextCursor::MoveAnchor);
    textEdit->setTextCursor(cursor);
}

void MarkdownEditor::adjustParsedBlockCount(int blockNum) {
    int blockCnt = this->document()->blockCount();
    int parsedBlockCnt = this->getParsedBlockNum();
    if (blockCnt > parsedBlockCnt) {
        int num = blockCnt - parsedBlockCnt;
        QTextBlock block = this->findParsedLastBlock(blockNum);
        QTextCursor cursor(block);
        cursor.beginEditBlock();
        cursor.movePosition(QTextCursor::EndOfBlock, QTextCursor::MoveAnchor);
        while (num--) {
            cursor.insertBlock();
            this->_blockNums.insert(block.blockNumber() + 1, 1);
        }
        cursor.endEditBlock();
    } else if (blockCnt < parsedBlockCnt) {
        int num = parsedBlockCnt - blockCnt;
        QTextBlock block = this->findParsedLastBlock(blockNum);
        block = block.next();
        blockNum = block.blockNumber();
        num = this->countParsedBlock(num, blockNum);
        while (num--) {
            QTextCursor cursor(block);
            block = block.next();
            cursor.select(QTextCursor::BlockUnderCursor);
            cursor.removeSelectedText();
            this->_blockNums.removeAt(blockNum);
        }
    }
}


void MarkdownEditor::parseBlock(int blockNum) {
    int originNum = blockNum;
    this->adjustParsedBlockCount(blockNum);
    QTextBlock block = this->findParsedBlock(blockNum);
    blockNum = block.blockNumber();
    int num = this->_blockNums[blockNum] - 1;
    while (num--) {
        QTextCursor cursor(block);
        block = block.next();
        cursor.select(QTextCursor::BlockUnderCursor);
        if (blockNum == 0) {
            cursor.deleteChar();
            cursor.deleteChar();
        } else {
            cursor.removeSelectedText();
        }
        this->_blockNums.removeAt(blockNum);
    }
    int cnt1 = this->_parsedDocument->blockCount();
    QTextCursor cursor(block);
    cursor.beginEditBlock();
    cursor.movePosition(QTextCursor::StartOfBlock, QTextCursor::MoveAnchor);
    cursor.movePosition(QTextCursor::EndOfBlock, QTextCursor::KeepAnchor);
    cursor.removeSelectedText();
    cursor.insertHtml(this->_parser.generateHtml(this->document()->findBlockByNumber(originNum)));
    cursor.endEditBlock();
    int cnt2 = this->_parsedDocument->blockCount();
    for (int i = 0; i < cnt2 - cnt1; ++i) {
        this->_blockNums.insert(blockNum + 1, 0);
    }
    this->_blockNums[blockNum] = cnt2 - cnt1 + 1;
}
