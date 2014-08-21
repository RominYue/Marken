#ifndef COLORSCHEME_H
#define COLORSCHEME_H

#include <QMap>
#include <QString>
#include "colorschemenode.h"

class ColorScheme {
public:
    ColorScheme();
    virtual ~ColorScheme();

    const QString& fontFamily() const;
    int fontSize() const;
    const QMap<QString, ColorSchemeNode>& colors() const;
    const ColorSchemeNode& color(const QString &section) const;

    void setFontFamily(const QString &family);
    void setFontSize(int size);
    void setColor(const QString &section, const ColorSchemeNode &color);

    void setForeground(const QString &section, const QColor &foreground);
    void setBackground(const QString &section, const QColor &background);
    void setBold(const QString &section, bool value);
    void setItalic(const QString &section, bool value);

private:
    QString _fontFamily;
    int _fontSize;
    QMap<QString, ColorSchemeNode> _colors;
};

#endif // COLORSCHEME_H
