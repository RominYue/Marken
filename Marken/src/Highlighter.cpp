#include <string>
#include "ParseLineData.h"
#include "ParseElementBlock.h"
#include "ParseElementSpan.h"
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
        ParseLineData* prevLine = nullptr;
        if (prevData != nullptr) {
            prevLine = prevData->data();
        }
        ParseLineData* nextLine = nullptr;
        if (nextData != nullptr) {
            nextLine = nextData->data();
        }
        currentData->data()->setNeighbor(prevLine, nextLine);
        currentBlock.setUserData(currentData);
    }
    if (this->_parser != nullptr) {
        this->_parser->parseLine(currentData->data(), text);
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
        if (currentData->data()->blocks.size() > 0) {
            if (currentData->data()->lastType() != ParseElementType::TYPE_PARAGRAPH) {
                if (prevData != nullptr) {
                    this->_parser->parseSpan(prevData->data());
                    this->highlight(prevBlock);
                }
            }
        }
        this->setCurrentBlockState(this->currentBlockState() + 1);
    }
    currentData->data()->saveLineStatus();
}

void Highlighter::highlight(QTextBlock block) {
    BlockData* data = dynamic_cast<BlockData*>(block.userData());
    if (data != nullptr) {
        ColorSchemeSetting& setting = Setting::instance()->colorSetting;
        ColorScheme& scheme = setting.colorScheme();
        ParseLineData* line = data->data();
        QTextCursor cursor(block);
        cursor.movePosition(QTextCursor::StartOfBlock, QTextCursor::MoveAnchor);
        cursor.movePosition(QTextCursor::EndOfBlock, QTextCursor::KeepAnchor);
        cursor.mergeCharFormat(scheme.format(ParseElementType::TYPE_PARAGRAPH));
        for (auto block : line->blocks) {
            if (block->type() == ParseElementType::TYPE_EMPTY ||
                block->type() == ParseElementType::TYPE_INVALID) {
                continue;
            }
            int offset = block->offset;
            int length = block->length;
            cursor.movePosition(QTextCursor::StartOfBlock, QTextCursor::MoveAnchor);
            for (int i = 0; i < offset; ++i) {
                cursor.movePosition(QTextCursor::NextCharacter, QTextCursor::MoveAnchor);
            }
            for (int i = 0; i < length; ++i) {
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
            int offset = span->offset;
            int length = span->length;
            cursor.movePosition(QTextCursor::StartOfBlock, QTextCursor::MoveAnchor);
            for (int i = 0; i < offset; ++i) {
                cursor.movePosition(QTextCursor::NextCharacter, QTextCursor::MoveAnchor);
            }
            for (int i = 0; i < length; ++i) {
                cursor.movePosition(QTextCursor::NextCharacter, QTextCursor::KeepAnchor);
            }
            cursor.mergeCharFormat(scheme.format(span->type()));
        }
    }
}
