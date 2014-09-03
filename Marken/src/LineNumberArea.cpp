#include "Editor.h"
#include "LineNumberArea.h"

LineNumberArea::LineNumberArea(Editor *editor) : QWidget(editor) {
    this->_markdownEditor = editor;
}

QSize LineNumberArea::sizeHint() const {
    return QSize(this->_markdownEditor->lineNumberAreaWidth(), 0);
}

void LineNumberArea::paintEvent(QPaintEvent *event) {
    this->_markdownEditor->lineNumberAreaPaintEvent(event);
}
