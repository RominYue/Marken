#include <string>
#include "BlockData.h"
#include "Highlighter.h"
using namespace std;

Highlighter::Highlighter(QTextDocument *parent) :
    QSyntaxHighlighter(parent) {
}

void Highlighter::setParser(QSharedPointer<DynamicParser> parser) {
    this->_parser = parser;
}

void Highlighter::highlightBlock(const QString& text) {
    auto currentBlock = this->currentBlock();
    BlockData* currentData = dynamic_cast<BlockData*>(currentBlock.userData());
    auto prevBlock = currentBlock.previous();
    BlockData* prevData = dynamic_cast<BlockData*>(prevBlock.userData());
    auto nextBlock = currentBlock.next();
    BlockData* nextData = dynamic_cast<BlockData*>(nextBlock.userData());
    if (currentData == nullptr) {
        currentData = new BlockData();
        ParseLine* prevLine = nullptr;
        if (prevData != nullptr) {
            prevLine = prevData->data();
        }
        ParseLine* nextLine = nullptr;
        if (nextData != nullptr) {
            nextLine = nextData->data();
        }
        currentData->data()->setNeighbor(prevLine, nextLine);
        currentBlock.setUserData(currentData);
    }
    if (this->_parser != nullptr) {
        string line = text.toUtf8().constData();
        this->_parser->parseLine(currentData->data(), line);
    }
    if (currentData->data()->isLineStatusChanged()) {
        this->setCurrentBlockState(this->currentBlockState() + 1);
    }
    currentData->data()->saveLineStatus();
}
