#ifndef PREFERENCEEDITOR_H
#define PREFERENCEEDITOR_H

#include <QWidget>

namespace Ui {
class ColorSchemeWidget;
}

class ColorSchemeWidget : public QWidget {
    Q_OBJECT

public:
    explicit ColorSchemeWidget(QWidget *parent = 0);
    ~ColorSchemeWidget();

    void setup();

private:
    Ui::ColorSchemeWidget *ui;

private slots:
    void updateColorScheme(QString scheme);
};

#endif // PREFERENCEEDITOR_H
