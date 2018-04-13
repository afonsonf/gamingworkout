#include "mainwindow.h"
#include "ui_mainwindow.h"

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
    for(int i=0;i<10;i++){
        QPixmap pixmap(":/icon/semaforo/img/semaforo.png");
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
        ui->gamesL->addWidget(wh);
    }

    //comentario afonso
}

MainWindow::~MainWindow()
{
    delete ui;
}
