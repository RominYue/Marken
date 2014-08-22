#ifndef COLORWIDGET_H
#define COLORWIDGET_H

#include <QWidget>
#include <QPaintEvent>
#include <QMouseEvent>

class ColorWidget : public QWidget {
    Q_OBJECT

public:
    explicit ColorWidget(QWidget *parent = 0);
    ~ColorWidget();

    const QColor& color() const;
    void setColor(const QColor &color);

protected:
    void mouseReleaseEvent(QMouseEvent*) override final;
    void paintEvent(QPaintEvent*) override final;

private:
    QColor _color;

signals:
    void colorChanged(const QColor color);
};

#endif // COLORWIDGET_H
