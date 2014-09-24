#ifndef COLORSCHEME_H
#define COLORSCHEME_H

#include <QList>
#include <QColor>
#include <QString>
#include <QTextCharFormat>
#include "ParseElementType.h"

class ColorScheme {
public:
    ColorScheme();
    virtual ~ColorScheme();

    void save(const QString& path);
    void load(const QString& path);

    ParseElementType type(const QString& name) const;
    const QString name(const ParseElementType type) const;
    QList<ParseElementType> typeList() const;

    const QString& fontFamily() const;
    int fontSize() const;
    const QColor& foreground(const ParseElementType type) const;
    const QColor& background(const ParseElementType type) const;
    bool bold(const ParseElementType type) const;
    bool italic(const ParseElementType type) const;
    bool underline(const ParseElementType type) const;
    bool strikeout(const ParseElementType type) const;
    QTextCharFormat format(const ParseElementType type) const;

    void setFontFamily(const QString &family);
    void setFontSize(const int size);

    void setForeground(const ParseElementType type, const QColor &color);
    void setBackground(const ParseElementType type, const QColor &color);
    void setBold(const ParseElementType type, const bool val);
    void setItalic(const ParseElementType type, const bool val);
    void setUnderline(const ParseElementType type, const bool val);
    void setStrikeout(const ParseElementType type, const bool val);

private:
    QString _fontFamily;
    int _fontSize;
    QMap<ParseElementType, QColor> _foreground;
    QMap<ParseElementType, QColor> _background;
    QMap<ParseElementType, bool> _bold;
    QMap<ParseElementType, bool> _italic;
    QMap<ParseElementType, bool> _underline;
    QMap<ParseElementType, bool> _strikeout;
    QMap<ParseElementType, QTextCharFormat> _format;

    QMap<QString, ParseElementType> _type;
};

#endif // COLORSCHEME_H
