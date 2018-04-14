#include "caesgatos.h"
#include "ui_caesgatos.h"

CaesGatos::CaesGatos(QWidget *parent,QPushButton *b) :
    QWidget(parent),
    ui(new Ui::CaesGatos)
{
    ui->setupUi(this);
    back = b;
    init_win();
}


CaesGatos::~CaesGatos()
{
    delete ui;
}

void CaesGatos::init_win()
{
    ui->gridLayout->setSpacing(5);
    for(int i=0;i<8;i++){
        for(int j=0;j<8;j++){
            m[i][j] = new QPushButton;
            m[i][j]->setFixedHeight(70);
            m[i][j]->setFixedWidth(70);
            connect(m[i][j],&QPushButton::clicked, [=]() {
                but_click(i,j);
            });
            QPixmap pixmap(":/img/img/nada.png");
            QIcon ButtonIcon(pixmap);
            m[i][j]->setIcon(ButtonIcon);
            m[i][j]->setIconSize(pixmap.rect().size());
            ui->gridLayout->addWidget(m[i][j],i,j);
        }
    }
    turn = 0;
    game_end=0;
    game_start = 1;
    first_player = 0;
}

void CaesGatos::but_click(int i,int j)
{

}

void CaesGatos::on_sair_clicked()
{
    back->click();
}
