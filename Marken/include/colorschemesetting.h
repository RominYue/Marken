#ifndef SETTINGEDITOR_H
#define SETTINGEDITOR_H

#include <QTextCharFormat>
#include "ColorScheme.h"

class ColorSchemeSetting {
public:
    ColorSchemeSetting();
    virtual ~ColorSchemeSetting();

    const QString& fontFamily() const;
    const QString& fontFamily(const QString &schemeName) const;
    int fontSize() const;
    int fontSize(const QString &schemeName) const;
    ColorScheme& scheme();
    ColorScheme &scheme(const QString &schemeName);

    void setCurrentScheme(const QString &schemeName);
    const QString& currentScheme() const;
    QMap<QString, ColorScheme>& schemes();

    void load();
    void save();

    bool isSchemeExist(const QString &schemeName) const;
    void cloneScheme(const QString &clone);
    void deleteScheme(const QString &schemeName);

    QFont font();
    QFont font(const QString &colorName);
    QTextCharFormat format();
    QTextCharFormat format(const QString &colorName);

private:
    QString _currentScheme;
    QMap<QString, ColorScheme> _schemes;

    int char2int(QChar c) const;
    char int2char(int val) const;
    int hex2int(QChar a, QChar b) const;
    QString int2hex(int val) const;
    QColor str2color(const QString &str) const;
    QString color2str(const QColor &color) const;
};

#endif // SETTINGEDITOR_H
