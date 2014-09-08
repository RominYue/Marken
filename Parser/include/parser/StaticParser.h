#ifndef PARSE_STATIC_H
#define PARSE_STATIC_H

#include <QString>
#include <QVector>

class StaticParser {
public:
    StaticParser();
    QVector<QString> ParserToHtmlList(const QVector<QString>& document) const;
    QString ParserToHtml(const QVector<QString>& document) const;
    QVector<QString> ParserToHtmlList(const QString& filePath) const;
    QString ParserToHtml(const QString& filePath) const;
    void ParserToFile(const QString& srcPath, const QString& tarPath) const;

private:
    void readDocument(const QString& filePath, QVector<QString>& document) const;
    void saveDocument(const QString& filePath, QVector<QString>& document) const;
};

#endif // PARSE_STATIC_H
