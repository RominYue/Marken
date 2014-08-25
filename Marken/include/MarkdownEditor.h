#ifndef MARKDOWNEDITOR_H
#define MARKDOWNEDITOR_H

#include <QKeyEvent>
#include <QPlainTextEdit>
#include "MarkdownParser.h"
#include "MarkdownHighlighter.h"

class MarkdownEditor : public QPlainTextEdit {
    Q_OBJECT
public:
    explicit MarkdownEditor(QWidget *parent = 0);

    QString name() const;
    QString path() const;

    void setPath(const QString &path);
    void open(const QString &path);
    void loadText();
    void save();
    void saveAs(const QString &path);

    void updateColorScheme();
    void rehighlight();

    void lineNumberAreaPaintEvent(QPaintEvent *event);
    int lineNumberAreaWidth();

    void spaceIndent();
    void multilineIndent(bool increase);
    void autoIndent();

    void addAtxHeader(int num);
    void addSetextHeader(int num);
    void addHorizonLine();
    void addInlineLink();
    void addInlineCode();
    void addInlineImage();
    void addReferenceLink();
    void addOrderedList();
    void addUnorderedList();
    void multilineList(bool ordered);
    void addQuote();
    void addUnquote();
    void multilineQuote(bool increase);
    void addLinkLabel();
    void addEmphasis();
    void addBold();

protected:
    void keyPressEvent(QKeyEvent *e);

private:
    QWidget *_lineNumberArea;

    MarkdownHighlighter *_highlighter;

    QString _name;
    QString _path;

    MarkdownParser _parser;

protected:
    void resizeEvent(QResizeEvent *event);

private slots:
    void updateLineNumberAreaWidth(int newBlockCount);
    void updateLineNumberArea(const QRect &, int);
    void highlightCurrentLine();
};

class LineNumberArea : public QWidget {
public:
    LineNumberArea(MarkdownEditor *editor) : QWidget(editor) {
        this->_markdownMarkdownEditor = editor;
    }

    QSize sizeHint() const {
        return QSize(this->_markdownMarkdownEditor->lineNumberAreaWidth(), 0);
    }

protected:
    void paintEvent(QPaintEvent *event) {
        this->_markdownMarkdownEditor->lineNumberAreaPaintEvent(event);
    }

private:
    MarkdownEditor *_markdownMarkdownEditor;
};

#endif // MARKDOWNEDITOR_H
