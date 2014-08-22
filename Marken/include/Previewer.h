#ifndef PREVIEWER_H
#define PREVIEWER_H

#include <QWidget>
#include "Editor.h"

namespace Ui {
class Previewer;
}

class Previewer : public QWidget {
    Q_OBJECT

public:
    explicit Previewer(QWidget *parent = 0);
    ~Previewer();

    void showPreview(Editor* editor);

private:
    Ui::Previewer *ui;
};

#endif // PREVIEWER_H
