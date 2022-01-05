#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QPainter>
#include <ctime>
#include <unistd.h>
#include <QKeyEvent>
#include  <QDebug>

#include <chrono>
#include <thread>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow :: paintEvent(QPaintEvent *e) {
    srand(time(NULL));
    QPainter painter(this);
    cor = rand()%4;
    if(cor==0){
        painter.setBrush(Qt::blue);
    }
    else if(cor == 1){
        painter.setBrush(Qt::red);
    }
    else if(cor == 2){
        painter.setBrush(Qt::yellow);
    }
    else if(cor == 3){
        painter.setBrush(Qt::green);
    }
    painter.drawEllipse(rand()%150,rand()%150,80,80);
    QWidget :: paintEvent(e);
}

void MainWindow :: keyPressEvent(QKeyEvent *e){
    using std::chrono::high_resolution_clock;
    using std::chrono::duration_cast;
    using std::chrono::duration;
    using std::chrono::milliseconds;

    auto t1 = high_resolution_clock::now();

    tecla = char(e->key());
    if(cor == 0 && tecla == 'W'){
        score +=1;
    }
    else if(cor == 1 && tecla == 'S'){
        score +=1;
    }
    else if(cor == 2 && tecla == 'A'){
        score +=1;
    }
    else if(cor == 3 && tecla == 'D'){
        score +=1;
    }
    else{
        score-=1;
    }
    QWidget ::update();

    auto t2 = high_resolution_clock::now();
    duration<double, std::milli> ms_double = t2 - t1;
    qDebug ()  << ms_double.count() <<  endl  <<  endl ;
}



