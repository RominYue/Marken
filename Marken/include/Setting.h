#ifndef SETTING_H
#define SETTING_H

#include "ColorScheme.h"
#include "ColorSchemeSetting.h"

class Setting {
public:
    static Setting* instance();
    ColorSchemeSetting colorSetting;

private:
    static Setting* _instance;
    Setting();
};

#endif // SETTING_H
