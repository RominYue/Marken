#ifndef MARKDOWNBLOCKDATA_H
#define MARKDOWNBLOCKDATA_H

#include <QTextBlockUserData>
#include "ParseLineData.h"

class BlockData : public QTextBlockUserData {
public:
    BlockData();

    ParseLineData* data();

private:
    ParseLineData _data;
};

#endif // MARKDOWNBLOCKDATA_H
