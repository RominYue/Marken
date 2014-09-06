#ifndef COLORSCHEMEFORM_H
#define COLORSCHEMEFORM_H

#include <QWidget>
#include <QListWidgetItem>

namespace Ui {
class ColorSchemeForm;
}

class ColorSchemeForm : public QWidget {
    Q_OBJECT

public:
    explicit ColorSchemeForm(QWidget *parent = 0);
    ~ColorSchemeForm();

private:
    Ui::ColorSchemeForm *ui;
    bool _schemeChanging;
    bool _colorChanging;

    void setup();
    void updateColorScheme();
    void updateColorItem(QListWidgetItem *item);

private slots:
    void on_fontComboBox_currentIndexChanged(const QString &family);
    void on_spinBoxSize_valueChanged(int size);
    void on_comboBoxScheme_currentIndexChanged(const QString &scheme);
    void on_pushButtonCopy_clicked();
    void on_pushButtonDelete_clicked();
    void on_listWidgetScheme_currentRowChanged(int currentRow);
    void on_checkBoxBold_toggled(bool checked);
    void on_checkBoxItalic_toggled(bool checked);
    void on_checkBoxUnderline_toggled(bool checked);
    void on_checkBoxStrikeout_toggled(bool checked);
    void colorWidgetForeground_changed(QColor color);
    void colorWidgetBackground_changed(QColor color);
};

#endif // COLORSCHEMEFORM_H
