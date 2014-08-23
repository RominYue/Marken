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

    this->highlighter = new MarkdownHighlighter(this->document());
    this->updateColorScheme();
    this->highlightCurrentLine();
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
    this->highlighter->rehighlight();
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
