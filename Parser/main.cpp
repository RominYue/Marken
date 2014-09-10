#include <cstdio>
#include <iostream>
#include <QFile>
#include <QString>
#include <QTextStream>
#include <QDebug>
#include "StaticParser.h"
using namespace std;

int main() {
    StaticParser parser;
    for (int i = 1; i <= 118; ++i) {
        QString fileName = QString("test/common/%1").arg(i);
        parser.ParserToFile(fileName + ".in", fileName + ".test");
        QString html1, html2;
        QFile fileOut(fileName + ".out");
        if (!fileOut.open(QIODevice::ReadOnly | QIODevice::Text)) {
            break;
        }
        QTextStream fout(&fileOut);
        fout.setCodec("UTF-8");
        while (!fout.atEnd()) {
            html1 += fout.readLine();
        }
        fileOut.close();
        QFile fileTest(fileName + ".test");
        if (!fileTest.open(QIODevice::ReadOnly | QIODevice::Text)) {
            break;
        }
        QTextStream ftest(&fileTest);
        ftest.setCodec("UTF-8");
        while (!ftest.atEnd()) {
            html2 += ftest.readLine();
        }
        fileTest.close();
        if (html1 != html2) {
            cout << "FAILED " + string(fileName.toLatin1().data()) << endl;
            cout << "Expect: " << endl;
            cout << string(html1.toLatin1().data()) << endl;
            cout << "Actual: " << endl;
            cout << string(html2.toLatin1().data()) << endl;
        } else {
            cout << "PASSED " + string(fileName.toLatin1().data()) << endl;
        }
    }
    getchar();
    return 0;
}
