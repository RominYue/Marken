#include "ParseElement.h"
#include "ParseElementHeaderAtx.h"
#include "ParseElementHeaderSetext.h"
#include "ParseElementSpan.h"
#include "ParseElementParagraph.h"
#include "ParseLineData.h"
#include "ParseElementPlain.h"
#include "ParseElementEscape.h"
#include "ParseElementAmp.h"
#include "ParseElementCodeInline.h"
#include "ParseElementEmphasis.h"
#include "ParseElementStrong.h"
#include "ParseElementHtmlInline.h"
#include "ParseElementLinkInline.h"
#include "ParseElementLinkLabel.h"
#include "ParseElementLinkReference.h"
#include "ParseElementImageInline.h"
#include "ParseElementImageReference.h"
#include "ParseElementLinkAutomatic.h"
#include "SpanParser.h"

SpanParser::SpanParser() {
    this->_spans.push_back(QSharedPointer<ParseElementSpan>(new ParseElementEscape()));
    this->_spans.push_back(QSharedPointer<ParseElementSpan>(new ParseElementAmp()));
    this->_spans.push_back(QSharedPointer<ParseElementSpan>(new ParseElementCodeInline()));
    this->_spans.push_back(QSharedPointer<ParseElementSpan>(new ParseElementStrong()));
    this->_spans.push_back(QSharedPointer<ParseElementSpan>(new ParseElementEmphasis()));
    this->_spans.push_back(QSharedPointer<ParseElementSpan>(new ParseElementLinkAutomatic()));
    this->_spans.push_back(QSharedPointer<ParseElementSpan>(new ParseElementHtmlInline()));
    this->_spans.push_back(QSharedPointer<ParseElementSpan>(new ParseElementLinkInline()));
    this->_spans.push_back(QSharedPointer<ParseElementSpan>(new ParseElementLinkReference()));
    this->_spans.push_back(QSharedPointer<ParseElementSpan>(new ParseElementImageInline()));
    this->_spans.push_back(QSharedPointer<ParseElementSpan>(new ParseElementImageReference()));
}

void SpanParser::ParserElement(QSharedPointer<ParseElement> elem) {
    if (elem->type() == ParseElementType::TYPE_PARAGRAPH) {
        this->ParserParagraphElement(qSharedPointerDynamicCast<ParseElementParagraph>(elem));
    } else if (elem->type() == ParseElementType::TYPE_HEADER_ATX) {
        this->ParserHeader(qSharedPointerDynamicCast<ParseElementHeader>(elem));
    } else if (elem->type() == ParseElementType::TYPE_HEADER_SETEXT) {
        this->ParserHeaderSetext(qSharedPointerDynamicCast<ParseElementHeaderSetext>(elem));
    }
}

int SpanParser::prevLineNum() const {
    return this->_prevLineNum;
}

int SpanParser::nextLineNum() const {
    return this->_nextLineNum;
}

void SpanParser::ParserHeader(QSharedPointer<ParseElementHeader> elem) {
    this->_prevLineNum = 0;
    this->_nextLineNum = 0;
    this->initSpanParent(elem->parent);
    auto text = elem->getCleanedHeader();
    auto spans = this->ParserLine(text, elem->offset + elem->getCleanStartIndex());
    for (auto span : spans) {
        span->openActivate = true;
        span->closeActivate = true;
    }
    elem->parent->removeCurrentSpans();
    elem->parent->spans = spans;
}

void SpanParser::ParserHeaderSetext(QSharedPointer<ParseElementHeaderSetext> elem) {
    if (elem->isLower()) {
        if (elem->parent->prev() != nullptr) {
            if (elem->parent->prev()->blocks.size() > 0) {
                auto lastElem = elem->parent->prev()->lastElement();
                if (lastElem->type() == ParseElementType::TYPE_HEADER_SETEXT) {
                    this->ParserHeader(qSharedPointerDynamicCast<ParseElementHeader>(lastElem));
                }
            }
        }
    }
}

void SpanParser::ParserParagraphElement(QSharedPointer<ParseElementParagraph> elem) {
    this->_prevLineNum = 0;
    this->_nextLineNum = 0;
    this->initSpanParent(elem->parent);
    auto begin = elem;
    while (!begin->isParagraphBegin()) {
        ++this->_prevLineNum;
        begin = qSharedPointerDynamicCast<ParseElementParagraph>(begin->parent->prev()->lastElement());
    }
    QVector<QString> paragraph;
    auto end = begin;
    while (!end->isParagraphEnd()) {
        ++this->_nextLineNum;
        paragraph.push_back(end->text);
        end->parent->removeCurrentSpans();
        end = qSharedPointerDynamicCast<ParseElementParagraph>(end->parent->next()->lastElement());
    }
    this->_nextLineNum -= this->_prevLineNum;
    paragraph.push_back(end->text);
    end->parent->removeCurrentSpans();
    auto spanVec = this->ParserParagraph(paragraph);
    end = begin;
    int index = 0;
    while (!end->isParagraphEnd()) {
        for (auto span : spanVec[index]) {
            span->offset += end->offset;
        }
        end->parent->spans = spanVec[index];
        end = qSharedPointerDynamicCast<ParseElementParagraph>(end->parent->next()->lastElement());
        ++index;
    }
    for (auto span : spanVec[index]) {
        span->offset += end->offset;
    }
    end->parent->spans = spanVec[index];
}

QVector<QSharedPointer<ParseElementSpan>> SpanParser::ParserLine(const QString& line, int shiftOffset) {
    QVector<QSharedPointer<ParseElementSpan>> spans;
    int last = 0, offset = 0;
    int lineLen = line.length();
    while (offset < lineLen) {
        bool flag = true;
        for (auto elem : this->_spans) {
            int length = elem->tryParse(line, offset);
            if (length > 0) {
                flag = false;
                if (offset > last) {
                    QSharedPointer<ParseElementPlain> plainText(new ParseElementPlain());
                    plainText->offset = shiftOffset + last;
                    plainText->length = offset - last;
                    plainText->text = line.mid(last, offset - last);
                    spans.push_back(plainText);
                }
                elem->offset = shiftOffset + offset;
                elem->length = length;
                elem->text = line.mid(offset, length);
                spans.push_back(this->_factory.copy(elem));
                QString innerText = elem->innerText();
                if (innerText.length() > 0) {
                    auto innerElems = this->ParserLine(innerText, elem->offset + elem->innerOffset());
                    for (auto inner : innerElems) {
                        spans.push_back(inner);
                    }
                }
                offset += length;
                last = offset;
                break;
            }
        }
        if (flag) {
            ++offset;
        }
    }
    if (offset > last) {
        QSharedPointer<ParseElementPlain> plainText(new ParseElementPlain());
        plainText->offset = shiftOffset + last;
        plainText->length = offset - last;
        plainText->text = line.mid(last, offset - last);
        spans.push_back(plainText);
    }
    return spans;
}

QVector<QVector<QSharedPointer<ParseElementSpan>>> SpanParser::ParserParagraph(const QVector<QString>& paragraph) {
    QString line;
    int lineNum = paragraph.size();
    QVector<int> lengths;
    QVector<QVector<QSharedPointer<ParseElementSpan>>> spanVec;
    lengths.push_back(0);
    for (auto p : paragraph) {
        line += p;
        spanVec.push_back(QVector<QSharedPointer<ParseElementSpan>>());
        lengths.push_back((int)p.length());
    }
    for (int i = 1; i <= lineNum; ++i) {
        lengths[i] += lengths[i - 1];
    }
    auto spans = this->ParserLine(line, 0);
    for (auto span : spans) {
        int offset = span->offset;
        int length = span->length;
        int start = lineNum - 1;
        for (int i = 1; i <= lineNum; ++i) {
            if (offset < lengths[i]) {
                start = i;
                break;
            }
        }
        int end = lineNum - 1;
        for (int i = 1; i <= lineNum; ++i) {
            if (offset + length <= lengths[i]) {
                end = i;
                break;
            }
        }
        if (start == end) {
            span->openActivate = true;
            span->closeActivate = true;
            span->offset = span->offset - lengths[start - 1];
            spanVec[start - 1].push_back(this->_factory.copy(span));
        } else {
            QString text = span->text;
            int offset = span->offset;
            int length = span->length;
            span->openActivate = true;
            span->closeActivate = false;
            span->offset = offset - lengths[start - 1];
            span->length = lengths[start] - offset;
            span->text = text.mid(0, lengths[start] - span->offset);
            spanVec[start - 1].push_back(this->_factory.copy(span));
            for (int i = start + 1; i < end; ++i) {
                span->openActivate = false;
                span->closeActivate = false;
                span->offset = 0;
                span->length = lengths[i] - lengths[i - 1];
                if (span->type() == ParseElementType::TYPE_PLAIN) {
                    span->openActivate = true;
                }
                span->text = text.mid(lengths[i - 1] - span->offset, lengths[i] - lengths[i - 1]);
                spanVec[i - 1].push_back(this->_factory.copy(span));
            }
            span->openActivate = false;
            span->closeActivate = true;
            span->offset = 0;
            span->length = offset + length - lengths[end - 1];
            if (span->type() == ParseElementType::TYPE_PLAIN) {
                span->openActivate = true;
            }
            span->text = text.mid(lengths[end - 1] - span->offset, span->offset + text.length() - lengths[end - 1]);
            spanVec[end - 1].push_back(this->_factory.copy(span));
        }
    }
    return spanVec;
}

void SpanParser::initSpanParent(ParseLineData* parent) {
    for (auto span : this->_spans) {
        span->parent = parent;
    }
}
