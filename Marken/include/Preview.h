#ifndef PREVIEWER_H
#define PREVIEWER_H

#include <QSet>
#include <QWidget>
#include "Editor.h"

namespace Ui {
class Preview;
}

class Preview : public QWidget {
    Q_OBJECT

public:
    explicit Preview(QWidget *parent = 0);
    ~Preview();

    void scrollToLine(int lineNum);
    void showPreview(Editor *editor);
    void changePreview(Editor *editor);
    void updateColorScheme();

private:
    Ui::Preview *ui;
    QString _tempName;
    QSet<int> _lineAnchors;

    QString getLineNumAnchor(int lineNum) const;
};

#endif // PREVIEWER_H
