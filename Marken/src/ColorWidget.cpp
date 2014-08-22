#include <QColorDialog>
#include <QPainter>
#include "ColorWidget.h"

ColorWidget::ColorWidget(QWidget *parent) :
    QWidget(parent) {
}

ColorWidget::~ColorWidget() {
}

const QColor& ColorWidget::color() const {
    return this->_color;
}

void ColorWidget::setColor(const QColor &color) {
    this->_color = color;
    this->update();
}

void ColorWidget::mouseReleaseEvent(QMouseEvent*) {
    QColor color = QColorDialog::getColor(this->_color, this);
    if (this->_color != color) {
        this->_color = color;
        this->update();
        emit colorChanged(color);
    }
}

void ColorWidget::paintEvent(QPaintEvent*) {
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing, true);
    painter.setPen(Qt::NoPen);
    painter.setBrush(Qt::black);
    painter.drawRect(0, 0, this->width(), this->height());
    painter.setBrush(this->_color);
    painter.drawRect(3, 3, this->width() - 6, this->height() - 6);
    painter.setBrush(Qt::black);
    QPointF points[3] = {
        QPointF(this->width(), this->height()),
        QPointF(this->width() - 9, this->height()),
        QPointF(this->width(), this->height() - 9)
    };
    painter.drawPolygon(points, 3);
}
