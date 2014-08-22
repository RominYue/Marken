#ifndef PREVIEWER_H
#define PREVIEWER_H

#include <QWidget>

namespace Ui {
class Previewer;
}

class Previewer : public QWidget {
    Q_OBJECT

public:
    explicit Previewer(QWidget *parent = 0);
    ~Previewer();

private:
    Ui::Previewer *ui;
};

#endif // PREVIEWER_H
