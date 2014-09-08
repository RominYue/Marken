#ifndef PARSE_ELEM_CODE_FENCE_H
#define PARSE_ELEM_CODE_FENCE_H

#include "parse_elem_block.h"

class ParseElementCodeFence : public ParseElementBlock {
public:
    ParseElementCodeFence();
    virtual ParseElementType type() const override final;

    virtual bool inheritable() const override final;
    virtual bool tryParse(const string &line, int offset, int& length) override final;

    virtual string generateOpenHtml() const override final;
    virtual string generateCloseHtml() const override final;

private:
    bool _isClose;
    char _fenceChar;
    int _fenceLen;
    int _fenceOffset;
    string _language;
};

#endif // PARSE_ELEM_CODE_FENCE_H
