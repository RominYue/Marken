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
        LINE_NESTED_BLOCK,
        LINE_LINK_LABEL,
        LINE_INVALID,
    };

    MarkdownBlockData();
    LineType type() const;
    void setType(LineType type);
    void setHtmlTag(const QString &tag);
    const QString& htmlTag() const;

private:
    LineType _type;
    QString _htmlTag; // Record the start block level HTML tag.
};

#endif // MARKDOWNBLOCKDATA_H
