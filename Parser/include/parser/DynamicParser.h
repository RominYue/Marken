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
    void parseLine(ParseLineData* data, QString line);
    void parseSpan(ParseLineData* data);

    int prevLineNum() const;
    int nextLineNum() const;

    ParseLabelSet linkLabelSet;

private:
    SpanParser _spanParser;
    QVector<QSharedPointer<ParseElementBlock>> _blocks;

    int _prevLineNum;
    int _nextLineNum;
};

#endif // PARSE_DYNAMIC_H
