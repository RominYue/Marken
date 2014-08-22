#include <QString>
#include <MarkdownCompiler.h>
#include <QStringList>
#include "MarkdownTest.h"

MarkdownTest::MarkdownTest() {
}

void MarkdownTest::htmlTest() {
    MarkdownCompiler compiler;
    QFETCH(QString, input);
    QFETCH(QString, result);
    QStringList list = input.split('\n');
    QString output = compiler.parseToHTML(list);
    QCOMPARE(output, result);
}

void MarkdownTest::testAtxHeader() {
    this->htmlTest();
}

void MarkdownTest::testAtxHeader_data() {
    QTest::addColumn<QString>("input");
    QTest::addColumn<QString>("result");
    QTest::newRow("Header Empty") << "#" << "<h1></h1>\n<hr>\n";
    QTest::newRow("Header 1 Normal") << "#Header 1" << "<h1>Header 1</h1>\n<hr>\n";
    QTest::newRow("Header 2 Normal") << "##Header 2" << "<h2>Header 2</h2>\n<hr>\n";
    QTest::newRow("Header 3 Normal") << "###Header 3" << "<h3>Header 3</h3>\n<hr>\n";
    QTest::newRow("Header 4 Normal") << "####Header 4" << "<h4>Header 4</h4>\n";
    QTest::newRow("Header 5 Normal") << "#####Header 5" << "<h5>Header 5</h5>\n";
    QTest::newRow("Header 6 Normal") << "######Header 6" << "<h6>Header 6</h6>\n";
    QTest::newRow("Header With Spaces Pre") << "# Header 1" << "<h1>Header 1</h1>\n<hr>\n";
    QTest::newRow("Header With Spaces Suf") << "#Header 1 " << "<h1>Header 1</h1>\n<hr>\n";
    QTest::newRow("Header With Spaces All") << "# Header 1 " << "<h1>Header 1</h1>\n<hr>\n";
    QTest::newRow("Header With Suffix Hashes") << "# Header 1 ###" << "<h1>Header 1</h1>\n<hr>\n";
}

void MarkdownTest::testSetextHeader() {
    this->htmlTest();
}

void MarkdownTest::testSetextHeader_data() {
    QTest::addColumn<QString>("input");
    QTest::addColumn<QString>("result");
    QTest::newRow("Header 1 Len 1") << "Header 1\n=" << "<h1>Header 1</h1>\n<hr>\n";
    QTest::newRow("Header 1 Len 2") << "Header 1\n==" << "<h1>Header 1</h1>\n<hr>\n";
    QTest::newRow("Header 1 Len 3") << "Header 1\n===" << "<h1>Header 1</h1>\n<hr>\n";
    QTest::newRow("Header 2 Len 1") << "Header 2\n-" << "<h2>Header 2</h2>\n<hr>\n";
    QTest::newRow("Header 2 Len 2") << "Header 2\n--" << "<h2>Header 2</h2>\n<hr>\n";
    QTest::newRow("Header 2 Len 3") << "Header 2\n---" << "<h2>Header 2</h2>\n<hr>\n";
    QTest::newRow("Header Width Spaces") << "  Header 1  \n=" << "<h1>Header 1</h1>\n<hr>\n";
    QTest::newRow("Header Width Hashes") << "#  Header 1  #\n=" << "<h1>Header 1</h1>\n<hr>\n";
}

void MarkdownTest::testHorizontal() {
    this->htmlTest();
}

void MarkdownTest::testHorizontal_data() {
    QTest::addColumn<QString>("input");
    QTest::addColumn<QString>("result");
    QTest::newRow("Horizon +") << "+++" << "<hr>\n";
    QTest::newRow("Horizon -") << "---" << "<hr>\n";
    QTest::newRow("Horizon _") << "___" << "<hr>\n";
    QTest::newRow("Horizon Not Enough _") << "_" << "<p>\n_\n</p>\n";
    QTest::newRow("Horizon Spaces +") << "+  +  +" << "<hr>\n";
}
