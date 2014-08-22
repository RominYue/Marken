#ifndef EDITOR_H
#define EDITOR_H

#include <QWidget>
#include <QTextEdit>
#include "MarkdownHighlighter.h"

namespace Ui {
class Editor;
}

class Editor : public QWidget {
    Q_OBJECT

public:
    explicit Editor(QWidget *parent = 0);
    ~Editor();

    QString name() const;
    QString path() const;
    bool isModified() const;

    void setPath(const QString &path);
    void open(const QString &path);
    void save();
    void saveAs(const QString &path);

    QTextEdit* textEdit() const;

    void updateColorScheme();
    void rehighlight();

private:
    Ui::Editor *ui;
    MarkdownHighlighter *highlighter;
    int _lastLength;

    QString _name;
    QString _path;
    bool _modified;

    void updateTitle();

private slots:
    void on_textEdit_textChanged();
};

#endif // EDITOR_H
