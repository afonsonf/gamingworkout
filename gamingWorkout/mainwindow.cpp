#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "semaforo.h"

#include <QPushButton>
#include <QTextEdit>
#include <QLabel>
#include <QWidget>
#include <QDebug>

Semaforo *s;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    begin_win();
    Semaforo *s = new Semaforo();
    s->show();
    //comentario afonso
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::begin_win(){
    for(int i=0;i<10;i++){
        QPixmap pixmap(":/img/semaforo/img/semaforo.png");
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
}

void MainWindow::show_s(){
    s = new Semaforo();
}
