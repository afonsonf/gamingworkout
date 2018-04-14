#include "produto.h"
#include "ui_produto.h"

produto::produto(QWidget *parent,QPushButton *b) :
    QWidget(parent),
    ui(new Ui::produto)
{
    ui->setupUi(this);
    back = b;
}

produto::~produto()
{
    delete ui;
}

void produto::on_sair_2_clicked()
{
    back->click();
}
