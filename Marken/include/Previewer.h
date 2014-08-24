#ifndef PREVIEWER_H
#define PREVIEWER_H

#include <QWidget>
#include "MarkdownEditor.h"

namespace Ui {
class Previewer;
}

class Previewer : public QWidget {
    Q_OBJECT

public:
    explicit Previewer(QWidget *parent = 0);
    ~Previewer();

    void showPreview(MarkdownEditor* editor);

private:
    Ui::Previewer *ui;
    MarkdownEditor* _editor;

private slots:
    void scroll(const QRect &, int);
};

#endif // PREVIEWER_H
