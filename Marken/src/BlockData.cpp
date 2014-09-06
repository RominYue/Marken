#include "BlockData.h"

BlockData::BlockData() :
    QTextBlockUserData() {
}

ParseLine* BlockData::data() {
    return &this->_data;
}
