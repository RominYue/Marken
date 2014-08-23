#ifndef MARKDOWNBLOCKDATA_H
#define MARKDOWNBLOCKDATA_H

#include <QTextBlockUserData>

class MarkdownBlockData : public QTextBlockUserData {
public:
    enum LineType {
        LINE_DEFAULT,
        LINE_BLOCK_HTML,
        LINE_BLOCK_HTML_END,
        //LINE_ATX_HEADER_1,
        //LINE_ATX_HEADER_2,
        //LINE_ATX_HEADER_3,
        //LINE_ATX_HEADER_4,
        //LINE_ATX_HEADER_5,
        //LINE_ATX_HEADER_6,
        //LINE_SETEXT_HEADER_1,
        //LINE_SETEXT_HEADER_2,
        //LINE_BLOCK_QUOTE,
        //LINE_UNORDERED_LIST,
        //LINE_ORDERED_LIST,
        LINE_CODE_BLOCK_SINGLE,
        LINE_CODE_BLOCK_BEGIN,
        LINE_CODE_BLOCK_MID,
        LINE_CODE_BLOCK_END,
        //LINE_HORIZONTAL,
        //LINE_LINK_LABEL,
    };

    MarkdownBlockData();
    QVector<LineType>* types();
    LineType firstType() const;
    LineType lastType() const;
    void setType(LineType type);
    void setHtmlTag(const QString &tag);
    const QString& htmlTag() const;
    void setHtml(const QString &html);
    const QString& html() const;
    void setText(const QString &text);
    const QString& text() const;

    void generateHtml();

private:
    QVector<LineType> _types;
    QString _htmlTag; // Record the start block level HTML tag.
    QString _html;
    QString _text;

    QString removeCodeIndent(const QString &str);
    QString translate(const QString &str);
};

#endif // MARKDOWNBLOCKDATA_H
