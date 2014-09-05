#include "Setting.h"

Setting* Setting::_instance = nullptr;

Setting::Setting() {
    this->colorSetting.load();
}

Setting* Setting::instance() {
    if (_instance == nullptr) {
        _instance = new Setting();
    }
    return _instance;
}
