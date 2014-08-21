#include "Previewer.h"
#include "ui_Previewer.h"

Previewer::Previewer(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Previewer) {
    ui->setupUi(this);
}

Previewer::~Previewer() {
    delete ui;
}
