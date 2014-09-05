#ifndef MARKDOWNEDITOR_H
#define MARKDOWNEDITOR_H

#include <QSharedPointer>
#include <QKeyEvent>
#include <QPlainTextEdit>
#include "parse_dynamic.h"

class LineNumberArea;
class Highlighter;

class Editor : public QPlainTextEdit {
    Q_OBJECT
public:
    explicit Editor(QWidget *parent = 0);

    QString name() const;
    QString path() const;
    QSharedPointer<DynamicParser> parser() const;

    void setPath(const QString &path);
    void open(const QString &path);
    void loadText();
    void save();
    void saveAs(const QString &path);
    void saveAsHtml(const QString &path);

    void rehighlight();
    int firstVisibleLineNum() const;

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
    void resizeEvent(QResizeEvent *event);

private:
    QWidget *_lineNumberArea;

    QString _name;
    QString _path;

    QSharedPointer<DynamicParser> _parser;
    Highlighter* _highlighter;

private slots:
    void updateLineNumberAreaWidth(int newBlockCount);
    void updateLineNumberArea(const QRect &, int);
    void highlightCurrentLine();
};

#endif // MARKDOWNEDITOR_H
