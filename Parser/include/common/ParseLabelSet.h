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
    void addLinkTitle(ParseElementLinkLabel* linkLabel);
    void removeLinkLabel(ParseElementLinkLabel* linkLabel);
    void removeLinkTitle(ParseElementLinkLabel* linkLabel);

    void addLinkElement(const QString& label, ParseElementLink* elem);
    void removeLinkElement(const QString& label, ParseElementLink* elem);

    QString getLink(const QString& label);
    QString getTitle(const QString& label);

private:
    QMap<QString, QList<QString>> _links;
    QMap<QString, QList<QString>> _titles;
    QMap<QString, QList<ParseElementLink*>> _elems;
};

#endif // PARSE_LABEL_SET_H
