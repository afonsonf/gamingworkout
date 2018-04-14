#include "caesgatos.h"
#include "ui_caesgatos.h"

CaesGatos::CaesGatos(QWidget *parent,QPushButton *b) :
    QWidget(parent),
    ui(new Ui::CaesGatos)
{
    ui->setupUi(this);
    back = b;
}

CaesGatos::~CaesGatos()
{
    delete ui;
}
