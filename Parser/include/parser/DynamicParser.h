#ifndef PARSE_DYNAMIC_H
#define PARSE_DYNAMIC_H

#include <QString>
#include <QVector>
#include <QSharedPointer>
#include "SpanParser.h"
#include "ParseLabelSet.h"

class ParseLineData;
class ParseElementBlock;
class ParseElementLinkLabel;
class ParseLabelSet;

class DynamicParser {
public:
    DynamicParser();
    virtual ~DynamicParser();
    void ParserLine(ParseLineData* data, QString line);
    void ParserSpan(ParseLineData* data);

    qint32 prevLineNum() const;
    qint32 nextLineNum() const;

private:
    SpanParser _spanParser;
    QVector<QSharedPointer<ParseElementBlock>> _blocks;
    ParseLabelSet _linkLabelSet;

    qint32 _prevLineNum;
    qint32 _nextLineNum;
};

#endif // PARSE_DYNAMIC_H
