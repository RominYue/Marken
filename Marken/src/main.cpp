#include "Marken.h"
#include <QApplication>

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    Marken w;
    w.show();

    return a.exec();
}