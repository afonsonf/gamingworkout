#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QPushButton>
#include <QDebug>
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    int j=0;
    for(int i=0;i<500;i++){
        QPushButton *p = new QPushButton;
        qDebug() << j << " " << i%3;
        if(i%3 == 0 && i>2) j++;
        ui->gridLayout->addWidget(p,j,i%3);
    }

    //comentario afonso
}

MainWindow::~MainWindow()
{
    delete ui;
}
