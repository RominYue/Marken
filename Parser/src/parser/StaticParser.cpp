#include <QFile>
#include <QTextStream>
#include <QSharedPointer>
#include "DynamicParser.h"
#include "ParseElementBlock.h"
#include "ParseElementLinkLabel.h"
#include "ParseLineData.h"
#include "StaticParser.h"

StaticParser::StaticParser() {
}

QVector<QString> StaticParser::ParserToHtmlList(const QVector<QString>& document) const {
    QVector<QString> htmlList;
    QVector<QSharedPointer<ParseLineData>> dataList;
    DynamicParser parser;
    for (auto line : document) {
        QSharedPointer<ParseLineData> data(new ParseLineData());
        if (dataList.size() == 0) {
            parser.parseLine(data.data(), line);
        } else {
            data->setNeighbor(dataList.last().data(), nullptr);
            parser.parseLine(data.data(), line);
        }
        dataList.push_back(data);
    }
    for (int i = dataList.size() - 1; i >= 0; --i) {
        for (auto block : dataList[i]->blocks) {
            if (block->type() == ParseElementType::TYPE_LINK_LABEL) {
                auto linkLabel = qSharedPointerDynamicCast<ParseElementLinkLabel>(block);
                parser.linkLabelSet.addLinkLabel(linkLabel.data());
            }
        }
    }
    for (auto data : dataList) {
        htmlList.push_back(data->generateHtml());
    }
    return htmlList;
}

QString StaticParser::ParserToHtml(const QVector<QString>& document) const {
    QString html;
    QVector<QString> htmlList = this->ParserToHtmlList(document);
    for (auto line : htmlList) {
        html += line + "\n";
    }
    return html;
}

QVector<QString> StaticParser::ParserToHtmlList(const QString& filePath) const {
    QVector<QString> document;
    this->readDocument(filePath, document);
    return this->ParserToHtmlList(document);
}

QString StaticParser::ParserToHtml(const QString& filePath) const {
    QVector<QString> document;
    this->readDocument(filePath, document);
    return this->ParserToHtml(document);
}

void StaticParser::ParserToFile(const QString& srcPath, const QString& tarPath) const {
    auto document = ParserToHtmlList(srcPath);
    this->saveDocument(tarPath, document);
}

void StaticParser::readDocument(const QString& filePath, QVector<QString>& document) const {
    QFile file(filePath);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        return;
    }
    QString buffer;
    QTextStream fin(&file);
    fin.setCodec("UTF-8");
    while (!fin.atEnd()) {
        buffer = fin.readLine();
        document.push_back(buffer);
    }
    file.close();
}

void StaticParser::saveDocument(const QString& filePath, QVector<QString>& document) const {
    QFile file(filePath);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        return;
    }
    QTextStream fout(&file);
    fout.setCodec("UTF-8");
    for (auto line : document) {
        fout << line << endl;
    }
    file.close();
}
