#include "Marken.h"
#include <QApplication>

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    QCoreApplication::setOrganizationDomain("Marken");
    QCoreApplication::setOrganizationName("Marken");
    QCoreApplication::setApplicationName("Marken");
    QCoreApplication::setApplicationVersion("1.0.0");
    Marken marken;
    marken.show();
    return app.exec();
}
