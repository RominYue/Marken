#include <QUrl>
#include <QMimeData>
#include "MarkdownTabWidget.h"

MarkdownTabWidget::MarkdownTabWidget(QWidget *parent) :
    QTabWidget(parent) {
}

void MarkdownTabWidget::dragEnterEvent(QDragEnterEvent *event) {
    if (event->mimeData()->hasUrls()) {
        event->acceptProposedAction();
    }
}

void MarkdownTabWidget::dropEvent(QDropEvent *event) {
    for (auto url : event->mimeData()->urls()) {
        emit openFile(url.toLocalFile());
    }
    event->acceptProposedAction();
}
