#ifndef PREFERENCEEDITOR_H
#define PREFERENCEEDITOR_H

#include <QWidget>

namespace Ui {
class PreferenceEditor;
}

class PreferenceEditor : public QWidget
{
    Q_OBJECT

public:
    explicit PreferenceEditor(QWidget *parent = 0);
    ~PreferenceEditor();

private:
    Ui::PreferenceEditor *ui;
};

#endif // PREFERENCEEDITOR_H
