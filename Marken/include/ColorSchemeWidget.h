#ifndef PREFERENCEEDITOR_H
#define PREFERENCEEDITOR_H

#include <QWidget>
#include <QListWidgetItem>

namespace Ui {
class ColorSchemeWidget;
}

class ColorSchemeWidget : public QWidget {
    Q_OBJECT

public:
    explicit ColorSchemeWidget(QWidget *parent = 0);
    ~ColorSchemeWidget();

private:
    Ui::ColorSchemeWidget *ui;
    bool _schemeChanging;
    bool _colorChanging;

    void setup();
    void updateColorItem(QListWidgetItem *item);

private slots:
    void updateColorScheme(QString scheme);
    void on_fontComboBox_currentTextChanged(const QString &family);
    void on_spinBoxFontSize_valueChanged(int size);
    void on_listWidgetScheme_currentRowChanged(int currentRow);
    void on_colorForeground_colorChanged(QColor color);
    void on_colorBackground_colorChanged(QColor color);
    void on_checkBoxBold_toggled(bool checked);
    void on_checkBoxItalic_toggled(bool checked);
    void on_comboBoxScheme_currentIndexChanged(const QString &arg1);
    void on_buttonCopy_clicked();
    void on_buttonDelete_clicked();
};

#endif // PREFERENCEEDITOR_H
