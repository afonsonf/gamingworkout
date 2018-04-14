#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "semaforo/semaforo.h"
#include "rastros/rastros.h"
#include "caesGatos/caesgatos.h"

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
    //semaforo
    {
        QPixmap pixmap(":/img/img/semaforo.png");
        QLabel *img = new QLabel;
        img->setPixmap(pixmap.scaled(200,200,Qt::IgnoreAspectRatio, Qt::FastTransformation));
        img->setFixedHeight(200);
        img->setFixedWidth(200);
        QPushButton *b = new QPushButton("play");
        QLabel *t = new QLabel("jogo semaforo");
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
    //rastros
    {
        QPixmap pixmap(":/img/img/rastros.jpg");
        QLabel *img = new QLabel;
        img->setPixmap(pixmap.scaled(200,200,Qt::IgnoreAspectRatio, Qt::FastTransformation));
        img->setFixedHeight(200);
        img->setFixedWidth(200);
        QPushButton *b = new QPushButton("play");
        QLabel *t = new QLabel("jogo Rastros");
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
            show_r();
         });
    }
    //caes gatos
    {
        QPixmap pixmap(":/img/img/caesgatos.jpeg");
        QLabel *img = new QLabel;
        img->setPixmap(pixmap.scaled(200,200,Qt::IgnoreAspectRatio, Qt::FastTransformation));
        img->setFixedHeight(200);
        img->setFixedWidth(200);
        QPushButton *b = new QPushButton("play");
        QLabel *t = new QLabel("jogo Caes e Gatos");
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
            show_cG();
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

void MainWindow::show_r(){
    rastros *s = new rastros(this,ui->back);
    //s->show();
    if(ui->stackedWidget->count()>1)ui->stackedWidget->removeWidget(ui->stackedWidget->widget(1));
    ui->stackedWidget->addWidget(s);
    ui->stackedWidget->setCurrentIndex(1);
    ui->back->setHidden(true);
    //ui->game->;
}

void MainWindow::show_cG(){
    CaesGatos *s = new CaesGatos(this,ui->back);
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
