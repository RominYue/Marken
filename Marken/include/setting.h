#ifndef SETTING_H
#define SETTING_H

#include "ColorSchemeSetting.h"

class Setting
{
public:
    static Setting* instance();
    ColorSchemeSetting colorScheme;

private:
    static Setting* _instance;
    Setting();
};

#endif // SETTING_H
