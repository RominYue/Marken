#ifndef PARSE_ELEM_IMAGE_H
#define PARSE_ELEM_IMAGE_H

#include "ParseElementSpan.h"
#include "ParseElementLink.h"

class ParseElementImage : public ParseElementSpan, public ParseElementLink {
public:
    ParseElementImage();
    virtual ~ParseElementImage() = default;

protected:
    QString _alt;
    QString _help;
    QString _link;
    QString _title;

    QString generateOpenImageHtml(const QString& link, const QString& alt, const QString& title) const;
};

#endif // PARSE_ELEM_IMAGE_H
