#ifndef SETTINGEDITOR_H
#define SETTINGEDITOR_H

#include "colorscheme.h"

class SettingEditor {
public:
    SettingEditor();
    ~SettingEditor();

    const QString& fontFamily() const;
    const QString& fontFamily(const QString &schemeName) const;
    int fontSize() const;
    int fontSize(const QString &schemeName) const;
    const ColorScheme& scheme() const;
    const ColorScheme& scheme(const QString &schemeName) const;

private:
    QString _currentScheme;
    QMap<QString, ColorScheme> _schemes;
};

#endif // SETTINGEDITOR_H
