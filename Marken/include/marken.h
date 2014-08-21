#ifndef MARKEN_H
#define MARKEN_H

#include <QMainWindow>
#include <QDropEvent>
#include <QDragEnterEvent>
#include <QCloseEvent>

namespace Ui {
class Marken;
}

class Marken : public QMainWindow
{
    Q_OBJECT

public:
    explicit Marken(QWidget *parent = 0);
    ~Marken();

    void closeEvent(QCloseEvent *event) override final;

private:
    bool tryOpen(const QString &path);
    bool trySave();
    bool tryCloseAll();

private slots:
    void on_actionNew_triggered();
    void on_actionOpen_triggered();
    void on_actionSave_triggered();
    void on_actionSave_As_triggered();
    void on_actionClose_triggered();
    void on_actionClose_All_triggered();
    void on_actionQuit_triggered();
    void on_tabWidget_tabCloseRequested(int index);

    void on_actionSave_All_triggered();

private:
    Ui::Marken *ui;
};

#endif // MARKEN_H
