#include "BlockData.h"

BlockData::BlockData() :
    QTextBlockUserData() {
}

ParseLineData* BlockData::data() {
    return &this->_data;
}
