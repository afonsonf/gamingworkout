#include "rastros.h"
#include "ui_rastros.h"

rastros::rastros(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::rastros)
{
    ui->setupUi(this);
}

rastros::~rastros()
{
    delete ui;
}
