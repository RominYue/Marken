#ifndef MARKDOWNTEST_H
#define MARKDOWNTEST_H

#include <QtTest>

class MarkdownTest : public QObject {
    Q_OBJECT
public:
    MarkdownTest();
    void htmlTest();

private slots:
    void testAtxHeader();
    void testAtxHeader_data();
    void testSetextHeader();
    void testSetextHeader_data();
    void testHorizontal();
    void testHorizontal_data();
};

#endif // MARKDOWNTEST_H
