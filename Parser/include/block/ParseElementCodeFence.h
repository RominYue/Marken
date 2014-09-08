#ifndef PARSE_ELEM_CODE_FENCE_H
#define PARSE_ELEM_CODE_FENCE_H

#include "ParseElementBlock.h"

class ParseElementCodeFence : public ParseElementBlock {
public:
    ParseElementCodeFence();
    virtual ~ParseElementCodeFence() = default;
    virtual ParseElementType type() const override final;

    virtual bool inheritable() const override final;
    virtual bool tryParse(const QString &line, qint32 offset, qint32& length) override final;

    virtual QString generateOpenHtml() const override final;
    virtual QString generateCloseHtml() const override final;

private:
    bool _isClose;
    QChar _fenceChar;
    qint32 _fenceLen;
    qint32 _fenceOffset;
    QString _language;
};

#endif // PARSE_ELEM_CODE_FENCE_H
