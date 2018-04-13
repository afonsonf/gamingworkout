#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "semaforo/semaforo.h"

#include <QPushButton>
#include <QTextEdit>
#include <QLabel>
#include <QWidget>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    begin_win();

    //comentario afonso
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::begin_win(){
    for(int i=0;i<10;i++){
        QPixmap pixmap(":/img/img/semaforo.png");
        QLabel *img = new QLabel;
        img->setPixmap(pixmap.scaled(200,200,Qt::IgnoreAspectRatio, Qt::FastTransformation));
        img->setFixedHeight(200);
        img->setFixedWidth(200);
        QPushButton *b = new QPushButton("play");
        QTextEdit *t = new QTextEdit("jogo");
        QWidget *wv = new QWidget;
        QWidget *wh = new QWidget;
        QHBoxLayout *hl = new QHBoxLayout;
        QVBoxLayout *vl = new QVBoxLayout;
        vl->addWidget(t);
        vl->addWidget(b);
        wv->setLayout(vl);
        hl->addWidget(img);
        hl->addWidget(wv);
        wh->setLayout(hl);
        ui->games_l->addWidget(wh);
        connect(b,&QPushButton::clicked, [=]() {
            show_s();
       });
    }
    ui->back->setHidden(true);
}

void MainWindow::show_s(){
    Semaforo *s = new Semaforo(this,ui->back);
    //s->show();
    if(ui->stackedWidget->count()>1)ui->stackedWidget->removeWidget(ui->stackedWidget->widget(1));
    ui->stackedWidget->addWidget(s);
    ui->stackedWidget->setCurrentIndex(1);
    ui->back->setHidden(true);
    //ui->game->;
}

void MainWindow::on_back_clicked()
{
    if(ui->stackedWidget->count()>1)ui->stackedWidget->removeWidget(ui->stackedWidget->widget(1));
    ui->stackedWidget->setCurrentIndex(0);
    ui->back->setHidden(true);
}
