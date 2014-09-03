#ifndef PREVIEWER_H
#define PREVIEWER_H

#include <QWidget>
#include "Editor.h"

namespace Ui {
class Preview;
}

class Preview : public QWidget {
    Q_OBJECT

public:
    explicit Preview(QWidget *parent = 0);
    ~Preview();

    void scrollToLine(int lineNum);
    void showPreview(Editor *editor);

private:
    Ui::Preview *ui;
};

#endif // PREVIEWER_H
