#ifndef MARKEN_H
#define MARKEN_H

#include <QMainWindow>

namespace Ui {
class Marken;
}

class Marken : public QMainWindow
{
    Q_OBJECT

public:
    explicit Marken(QWidget *parent = 0);
    ~Marken();

private:
    Ui::Marken *ui;
};

#endif // MARKEN_H
