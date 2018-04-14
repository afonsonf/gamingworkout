#include "avanco.h"
#include "ui_avanco.h"

avanco::avanco(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::avanco)
{
    ui->setupUi(this);
}

avanco::~avanco()
{
    delete ui;
}

