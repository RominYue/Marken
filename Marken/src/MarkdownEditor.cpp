#include <QPainter>
#include <QTextBlock>
#include "MarkdownEditor.h"

class LineNumberArea : public QWidget {
public:
    LineNumberArea(MarkdownEditor *editor) : QWidget(editor) {
        this->_markdownEditor = editor;
    }

    QSize sizeHint() const {
        return QSize(this->_markdownEditor->lineNumberAreaWidth(), 0);
    }

protected:
    void paintEvent(QPaintEvent *event) {
        this->_markdownEditor->lineNumberAreaPaintEvent(event);
    }

private:
    MarkdownEditor *_markdownEditor;
};

MarkdownEditor::MarkdownEditor(QWidget *parent) :
    QPlainTextEdit(parent) {
    this->_lineNumberArea = new LineNumberArea(this);
    this->connect(this, SIGNAL(blockCountChanged(int)), this, SLOT(updateLineNumberAreaWidth(int)));
    this->connect(this, SIGNAL(updateRequest(QRect,int)), this, SLOT(updateLineNumberArea(QRect,int)));
    this->updateLineNumberAreaWidth(0);
}

int MarkdownEditor::lineNumberAreaWidth() {
    int cnt = 0;
    int temp = this->blockCount() > 0 ? this->blockCount() : 1;
    while (temp) {
        temp /= 10;
        ++cnt;
    }
    return 3 + this->fontMetrics().width(QLatin1Char('0')) * cnt;
}

void MarkdownEditor::updateLineNumberAreaWidth(int) {
    this->setViewportMargins(lineNumberAreaWidth() + 3, 0, 0, 0);
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
            painter.drawText(0, top, this->_lineNumberArea->width(), fontMetrics().height(),
                             Qt::AlignRight, number);
        }
        block = block.next();
        top = bottom;
        bottom = top + (int) blockBoundingRect(block).height();
        ++blockNumber;
    }
}
