#include <string>
#include "parse_line.h"
#include "parse_elem_block.h"
#include "parse_elem_span.h"
#include "Setting.h"
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
        int prevLineNum = this->_parser->prevLineNum();
        while (prevLineNum--) {
            this->highlight(prevBlock);
            prevBlock = prevBlock.previous();
        }
        this->highlight(currentBlock);
        int nextLineNum = this->_parser->nextLineNum();
        while (nextLineNum--) {
            this->highlight(nextBlock);
            nextBlock = nextBlock.next();
        }
    }
    if (currentData->data()->isLineStatusChanged()) {
        this->setCurrentBlockState(this->currentBlockState() + 1);
    }
    currentData->data()->saveLineStatus();
}

void Highlighter::highlight(QTextBlock block) {
    BlockData* data = dynamic_cast<BlockData*>(block.userData());
    if (data != nullptr) {
        ColorSchemeSetting& setting = Setting::instance()->colorSetting;
        ColorScheme& scheme = setting.colorScheme();
        ParseLine* line = data->data();
        QTextCursor cursor(block);
        for (auto block : line->blocks) {
            if (block->type() == ParseElementType::TYPE_EMPTY ||
                block->type() == ParseElementType::TYPE_INVALID) {
                continue;
            }
            int utf8Offset = block->utf8Offset;
            int utf8Length = block->utf8Length;
            cursor.movePosition(QTextCursor::StartOfBlock, QTextCursor::MoveAnchor);
            for (int i = 0; i < utf8Offset; ++i) {
                cursor.movePosition(QTextCursor::NextCharacter, QTextCursor::MoveAnchor);
            }
            for (int i = 0; i < utf8Length; ++i) {
                cursor.movePosition(QTextCursor::NextCharacter, QTextCursor::KeepAnchor);
            }
            cursor.mergeCharFormat(scheme.format(block->type()));
        }
        for (auto span : line->spans) {
            if (span->type() == ParseElementType::TYPE_EMPTY ||
                span->type() == ParseElementType::TYPE_INVALID ||
                span->type() == ParseElementType::TYPE_PLAIN) {
                continue;
            }
            int utf8Offset = span->utf8Offset;
            int utf8Length = span->utf8Length;
            cursor.movePosition(QTextCursor::StartOfBlock, QTextCursor::MoveAnchor);
            for (int i = 0; i < utf8Offset; ++i) {
                cursor.movePosition(QTextCursor::NextCharacter, QTextCursor::MoveAnchor);
            }
            for (int i = 0; i < utf8Length; ++i) {
                cursor.movePosition(QTextCursor::NextCharacter, QTextCursor::KeepAnchor);
            }
            cursor.mergeCharFormat(scheme.format(span->type()));
        }
    }
}
