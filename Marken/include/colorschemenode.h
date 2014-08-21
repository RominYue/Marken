#ifndef COLORSCHEMENODE_H
#define COLORSCHEMENODE_H

#include <QColor>

class ColorSchemeNode {
public:
    ColorSchemeNode();
    ColorSchemeNode(const QColor& foreground, const QColor& background, bool bold, bool italic);
    virtual ~ColorSchemeNode();

    const QColor& foreground() const;
    const QColor& background() const;
    bool isBold() const;
    bool isItalic() const;

    void setForeground(const QColor &color);
    void setBackground(const QColor &color);
    void setBold(bool value);
    void setItalic(bool value);

private:
    QColor _foreground;
    QColor _background;
    bool _bold;
    bool _italic;
};

#endif // COLORSCHEMENODE_H
