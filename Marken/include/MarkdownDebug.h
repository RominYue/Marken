#ifndef MARKDOWNDEBUG_H
#define MARKDOWNDEBUG_H

#include <QTextDocument>
#include "MarkdownBlockData.h"

class MarkdownDebug {
public:
    MarkdownDebug();
    void saveBlockData(QTextDocument *document) const;

private:
    QString getDataTypeString(MarkdownBlockData::LineType type) const;
};

#endif // MARKDOWNDEBUG_H
