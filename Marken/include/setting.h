#ifndef SETTING_H
#define SETTING_H

class Setting
{
public:
    static Setting* instance();

private:
    static Setting* _instance;
    Setting();
};

#endif // SETTING_H
