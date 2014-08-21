#include "preferenceeditor.h"
#include "ui_preferenceeditor.h"

PreferenceEditor::PreferenceEditor(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::PreferenceEditor)
{
    ui->setupUi(this);
}

PreferenceEditor::~PreferenceEditor()
{
    delete ui;
}
