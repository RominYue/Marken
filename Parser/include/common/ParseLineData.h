#ifndef PARSE_LINE_H_INCLUDED
#define PARSE_LINE_H_INCLUDED

#include <QVector>
#include <QString>
#include <QSharedPointer>
#include "ParseElementType.h"

class ParseElement;
class ParseElementBlock;
class ParseElementSpan;
class ParseLabelSet;

class ParseLineData {
public:
    ParseLineData();
    virtual ~ParseLineData();

    ParseLineData* prev() const;
    ParseLineData* next() const;
    void setNeighbor(ParseLineData* prevLine, ParseLineData* nextLine);
    void removeFromList();

    void removeCurrentElements();
    void removeCurrentBlocks();
    void removeCurrentSpans();
    void saveLineStatus();
    bool isLineStatusChanged() const;

    QString generateHtml() const;

    QSharedPointer<ParseElementBlock> getElementAt(const int offset) const;
    ParseElementType getTypeAt(const int offset) const;
    int getIndexAt(const int offset) const;
    QSharedPointer<ParseElementBlock> lastElement() const;
    ParseElementType lastType() const;

    ParseLabelSet* labelSet;
    QVector<QSharedPointer<ParseElementBlock>> blocks;
    QVector<QSharedPointer<ParseElementSpan>> spans;

private:
    ParseLineData* _prev;
    ParseLineData* _next;
    QVector<QSharedPointer<ParseElementBlock>> _oldBlocks;
    QVector<QSharedPointer<ParseElementBlock>> _oldSpans;

    struct OffsetElement {
        QSharedPointer<ParseElementSpan> elem;
        int offset;
        bool isOpen;
        bool operator <(const OffsetElement& element) const {
            if (offset == element.offset) {
                return isOpen > element.isOpen;
            }
            return offset < element.offset;
        }
    };
};

#endif // PARSE_LINE_H_INCLUDED
