#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QPushButton>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    int j=0;
    for(int i=0;i<10;i++){
        QPushButton *p = new QPushButton;
        ui->gridLayout->addWidget(p,j,i%3);
        if(j%3 == 0 && !j) j++;
        j++;
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}
