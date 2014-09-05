#ifndef COLORSCHEMESETTING_H
#define COLORSCHEMESETTING_H

#include <QList>

class ColorScheme;

class ColorSchemeSetting {
public:
    ColorSchemeSetting();
    virtual ~ColorSchemeSetting();

    void save();
    void load();

    const QString& name() const;
    const QList<QString>& nameList() const;

    void selectScheme(const QString& name);
    bool copyScheme(const QString& name);
    bool deleteScheme(const QString& name);

    ColorScheme& colorScheme();

private:
    ColorScheme _scheme;
    QString _name;
    QList<QString> _nameList;

    void saveScheme();
    void loadScheme();
};

#endif // COLORSCHEMESETTING_H
