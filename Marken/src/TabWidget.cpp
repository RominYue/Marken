#include <QUrl>
#include <QMimeData>
#include "TabWidget.h"

TabWidget::TabWidget(QWidget *parent) :
    QTabWidget(parent) {
}

void TabWidget::dragEnterEvent(QDragEnterEvent *event) {
    if (event->mimeData()->hasUrls()) {
        event->acceptProposedAction();
    }
}

void TabWidget::dropEvent(QDropEvent *event) {
    for (auto url : event->mimeData()->urls()) {
        emit openFile(url.toLocalFile());
    }
    event->acceptProposedAction();
}
