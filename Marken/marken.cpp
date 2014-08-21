#include "marken.h"
#include "ui_marken.h"

Marken::Marken(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Marken)
{
    ui->setupUi(this);
}

Marken::~Marken()
{
    delete ui;
}
