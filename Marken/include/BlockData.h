#ifndef MARKDOWNBLOCKDATA_H
#define MARKDOWNBLOCKDATA_H

#include <QTextBlockUserData>
#include "parse_line.h"

class BlockData : public QTextBlockUserData {
public:
    BlockData();

    ParseLine* data();

private:
    ParseLine _data;
};

#endif // MARKDOWNBLOCKDATA_H
