#ifndef PARSE_SPAN_H
#define PARSE_SPAN_H

#include <QVector>
#include <QString>
#include <QSharedPointer>
#include "ParseElementFactory.h"

class ParseElement;
class ParseElementSpan;
class ParseElementParagraph;
class ParseElementHeader;
class ParseElementHeaderSetext;
class ParseLineData;

class SpanParser {
public:
    SpanParser();
    void ParserElement(QSharedPointer<ParseElement> elem);

    qint32 prevLineNum() const;
    qint32 nextLineNum() const;

private:
    qint32 _prevLineNum;
    qint32 _nextLineNum;

    ParseElementFactory _factory;
    QVector<QSharedPointer<ParseElementSpan>> _spans;
    void ParserHeader(QSharedPointer<ParseElementHeader> elem);
    void ParserHeaderSetext(QSharedPointer<ParseElementHeaderSetext> elem);
    void ParserParagraphElement(QSharedPointer<ParseElementParagraph> elem);
    QVector<QSharedPointer<ParseElementSpan>> ParserLine(const QString& line, qint32 offset);
    QVector<QVector<QSharedPointer<ParseElementSpan>>> ParserParagraph(const QVector<QString>& paragraph);

    void initSpanParent(ParseLineData* parent);
};

#endif // PARSE_SPAN_H
