#include "Setting.h"


Setting* Setting::_instance = nullptr;

Setting::Setting() {
}

Setting* Setting::instance() {
    if (_instance == nullptr) {
        _instance = new Setting();
    }
    return _instance;
}
