#ifndef MARKDOWNBLOCKDATA_H
#define MARKDOWNBLOCKDATA_H

#include <QTextBlockUserData>

class MarkdownBlockData : public QTextBlockUserData {
public:
    enum LineType {
        LINE_DEFAULT,
        LINE_EMPTY,
        LINE_BLOCK_HTML,
        LINE_BLOCK_HTML_END,
        LINE_ATX_HEADER_1,
        LINE_ATX_HEADER_2,
        LINE_ATX_HEADER_3,
        LINE_ATX_HEADER_4,
        LINE_ATX_HEADER_5,
        LINE_ATX_HEADER_6,
        LINE_SETEXT_HEADER_1,
        LINE_SETEXT_HEADER_2,
        LINE_CODE_BLOCK,
        LINE_HORIZONTAL,
        LINE_LINK_LABEL,
        LINE_BLOCK_QUOTE,
        LINE_ORDERED_LIST,
        LINE_UNORDERED_LIST,
        LINE_INVALID,
    };

    MarkdownBlockData();
    void clear();
    LineType type(int index) const;
    LineType typeAt(int indent) const;
    int indent(int index) const;
    QVector<LineType>* types();
    QVector<int>* indents();
    int lastIndent() const;
    void setLastIndent(int indent);
    void setHtmlTag(const QString &tag);
    const QString& htmlTag() const;

    void recordState();
    bool isStateChanged() const;

private:
    QVector<LineType> _types;
    QVector<int> _indents;
    int _lastIndent;
    QString _htmlTag; // Record the start block level HTML tag.

    QVector<LineType> _lastTypes;
    QVector<int> _lastIndents;
    int _lastLastIndent;
};

#endif // MARKDOWNBLOCKDATA_H
