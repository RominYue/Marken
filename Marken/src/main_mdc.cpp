#include <QFile>
#include <QTextStream>
#include <QStringList>
#include "MarkdownCompiler.h"

#ifdef QT_DEBUG

#include <QTest>
#include "MarkdownTest.h"

QTEST_APPLESS_MAIN(MarkdownTest)

#else

int main(int argc, char *argv[]) {
    if (argc == 3) {
        const char *inputPath = argv[1];
        const char *outputPath = argv[2];
        QFile inputFile(inputPath);
        if (!inputFile.open(QIODevice::ReadOnly | QIODevice::Text)) {
            return -1;
        }
        QTextStream in(&inputFile);
        QStringList list = in.readAll().split(QRegExp("[\r\n]"), QString::KeepEmptyParts);
        inputFile.close();
        MarkdownCompiler compiler;
        QString html = compiler.parseToHTML(list);
        QFile outputFile(outputPath);
        if (!outputFile.open(QIODevice::WriteOnly | QIODevice::Text)) {
            return -1;
        }
        QTextStream out(&outputFile);
        out.setCodec("UTF-8");
        out << html << endl;
        outputFile.close();
    }
    return 0;
}

#endif
