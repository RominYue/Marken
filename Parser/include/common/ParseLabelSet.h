#ifndef PARSE_LABEL_SET_H
#define PARSE_LABEL_SET_H

#include <QMap>
#include <QList>
#include <QString>
#include <QSharedPointer>
class ParseElementLink;
class ParseElementLinkLabel;

class ParseLabelSet {
public:
    ParseLabelSet();
    virtual ~ParseLabelSet();

    void addLinkLabel(ParseElementLinkLabel* linkLabel);

    QString getLink(const QString& label);
    QString getTitle(const QString& label);

private:
    QMap<QString, QString> _links;
    QMap<QString, QString> _titles;
};

#endif // PARSE_LABEL_SET_H
