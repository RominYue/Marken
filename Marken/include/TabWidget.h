#ifndef MARKDOWNTABWIDGET_H
#define MARKDOWNTABWIDGET_H

#include <QTabWidget>
#include <QDragEnterEvent>
#include <QDropEvent>

class TabWidget : public QTabWidget {
    Q_OBJECT
public:
    explicit TabWidget(QWidget *parent = 0);

protected:
    void dragEnterEvent(QDragEnterEvent *event);
    void dropEvent(QDropEvent *event);

signals:
    void openFile(QString path);
};

#endif // MARKDOWNTABWIDGET_H
