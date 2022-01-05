#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>
#include <QDebug>

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

void MainWindow::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    QPen pen;
    QBrush brush;
    pen.setWidth(3);
    pen.setColor(Qt::green);
    painter.setPen(pen);
    painter.drawRect(QRect(100,100,100,100));
    pen.setColor(Qt::red);
    painter.setPen(pen);
    painter.drawRect(QRect(205,100,100,100));
    pen.setColor(Qt::yellow);
    painter.setPen(pen);
    painter.drawRect(QRect(310,100,100,100));
    pen.setColor(Qt::blue);
    painter.setPen(pen);
    painter.drawRect(QRect(100,205,310,100));


    brush.setColor(Qt::green);
    brush.setStyle(Qt::SolidPattern);
    painter.setBrush(brush);
    pen.setColor(Qt::green);
    painter.setPen(pen);
    painter.drawRect(QRect(trem1x,trem1y,20,20));

    brush.setColor(Qt::red);
    brush.setStyle(Qt::SolidPattern);
    painter.setBrush(brush);
    pen.setColor(Qt::red);
    painter.setPen(pen);
    painter.drawRect(QRect(trem2x,trem2y,20,20));

    brush.setColor(Qt::yellow);
    brush.setStyle(Qt::SolidPattern);
    painter.setBrush(brush);
    pen.setColor(Qt::yellow);
    painter.setPen(pen);
    painter.drawRect(QRect(trem3x,trem3y,20,20));

    brush.setColor(Qt::blue);
    brush.setStyle(Qt::SolidPattern);
    painter.setBrush(brush);
    pen.setColor(Qt::blue);
    painter.setPen(pen);
    painter.drawRect(QRect(trem4x,trem4y,20,20));
}

void* desenha(void* arg)
{
    MainWindow* parametros;
    parametros = (MainWindow*)arg;
    while(1){

        if(!parametros->ui->velocidade_verde->isDown() &&
            !parametros->ui->velocidade_vermelho->isDown() &&
            !parametros->ui->velocidade_amarelo->isDown() &&
            !parametros->ui->velocidade_azul->isDown() &&
            !parametros->ui->velocidade_verde_2->isDown() &&
            !parametros->ui->velocidade_vermelho_2->isDown() &&
            !parametros->ui->velocidade_amarelo_2->isDown() &&
            !parametros->ui->velocidade_azul_2->isDown()){
            usleep(50000);
            parametros->repaint();
        }

    }
}

sem_t sem3;
sem_t sem4;
sem_t sem5;
sem_t sem6;
sem_t sem10;
sem_t sem436;
sem_t sem6510;

void* trem_1(void* arg)
{
    MainWindow* parametros;
    parametros = (MainWindow*)arg;
    while(1){
        //quadrado verde
        if(parametros->trem1x>=90 && parametros->trem1x<190 && parametros->trem1y==90){
            parametros->trem1x =parametros->trem1x + 5;
        }
        if(parametros->trem1x==190 && parametros->trem1y<190 && parametros->trem1y>=90){
            if(parametros->trem1y==90){
                sem_wait(&sem436);
                sem_wait(&sem3);
            }
            parametros->trem1y = parametros->trem1y + 5;
        }

        if(parametros->trem1x>90 && parametros->trem1x<=190 && parametros->trem1y==190){
            if(parametros->trem1x==190){
                sem_wait(&sem4);
                sem_post(&sem3);
                sem_post(&sem436);
            }
            parametros->trem1x = parametros->trem1x - 5;
        }
        if(parametros->trem1x==90 && parametros->trem1y<=190 && parametros->trem1y>90){
            if(parametros->trem1y==190){
                sem_post(&sem4);
            }
            parametros->trem1y = parametros->trem1y - 5;
        }
        usleep(parametros->velocidade1);
    }

}

void* trem_2(void* arg)
{
    MainWindow* parametros;
    parametros = (MainWindow*)arg;
     while(1){
        //quadrado vermelho
        if(parametros->trem2x<295 && parametros->trem2x>=195 && parametros->trem2y==90){
            parametros->trem2x =parametros->trem2x + 5;
        }
        if(parametros->trem2x==295 && parametros->trem2y<190 && parametros->trem2y>=90){
            if(parametros->trem2y==90){
                sem_wait(&sem6510);
                sem_wait(&sem5);
            }
            parametros->trem2y = parametros->trem2y + 5;
        }
        if(parametros->trem2x>195 && parametros->trem2x<=295 && parametros->trem2y==190){
            if(parametros->trem2x==295){
                //sem_wait(&sem4610);
                sem_wait(&sem436);
                sem_wait(&sem6);
                sem_post(&sem5);
                sem_post(&sem6510);
            }
            parametros->trem2x = parametros->trem2x - 5;
        }
        if(parametros->trem2x==195 && parametros->trem2y<=190 && parametros->trem2y>90){
            if(parametros->trem2y==190){
                sem_wait(&sem3);
                sem_post(&sem6);
                sem_post(&sem436);
                //sem_post(&sem4610);
            }
            parametros->trem2y = parametros->trem2y - 5;
            if(parametros->trem2y==90){
                sem_post(&sem3);
            }
        }
        usleep(parametros->velocidade2);
    }

}

void* trem_3(void* arg)
{
    MainWindow* parametros;
    parametros = (MainWindow*)arg;
     while(1){
         //quadrado amarelo
         if(parametros->trem3x<400 && parametros->trem3x>295 && parametros->trem3y==90){
             parametros->trem3x = parametros->trem3x + 5;
         }
         if(parametros->trem3x==400 && parametros->trem3y<190 && parametros->trem3y>=90){
             parametros->trem3y = parametros->trem3y + 5;
         }

         if(parametros->trem3x>=300 && parametros->trem3x<=400 && parametros->trem3y==190){
             if(parametros->trem3x==400){
                sem_wait(&sem5);
                //sem_wait(&sem4610);
                sem_wait(&sem6510);
                sem_wait(&sem10);
             }
             parametros->trem3x = parametros->trem3x - 5;
         }

         if(parametros->trem3x==300 && parametros->trem3y<=190 && parametros->trem3y>90){
             if(parametros->trem3y==190){
                //sem_wait(&sem5);
                sem_post(&sem10);
                sem_post(&sem6510);
                //sem_post(&sem4610);
             }
             parametros->trem3y = parametros->trem3y - 5;
             if(parametros->trem3y==90){
                sem_post(&sem5);
             }
         }
        usleep(parametros->velocidade3);
    }

}

void* trem_4(void* arg)
{
    MainWindow* parametros;
    parametros = (MainWindow*)arg;
     while(1){
         //retangulo azul
         if(parametros->trem4x<190 && parametros->trem4y==195){
             if(parametros->trem4x==90){
                //sem_wait(&sem4610);
                sem_wait(&sem436);
                sem_wait(&sem4);
             }
             parametros->trem4x = parametros->trem4x + 5;
         }

         if(parametros->trem4x>=190 && parametros->trem4x<290 && parametros->trem4y==195){
             if(parametros->trem4x==190){
                sem_wait(&sem6510);
                sem_wait(&sem6);
                sem_post(&sem4);
                sem_post(&sem436);
             }
             parametros->trem4x = parametros->trem4x + 5;
         }

         if(parametros->trem4x<400 && parametros->trem4x>=290 && parametros->trem4y==195){
            if(parametros->trem4x==290){
                sem_wait(&sem10);
                sem_post(&sem6);
                sem_post(&sem6510);
            }
            parametros->trem4x = parametros->trem4x + 5;
         }

         if(parametros->trem4x>=400 && parametros->trem4y<295){
             if(parametros->trem4y==195){
                sem_post(&sem10);
                //sem_post(&sem4610);
             }
             parametros->trem4y = parametros->trem4y + 5;
         }
         if(parametros->trem4x>=95 && parametros->trem4y==295){
             parametros->trem4x = parametros->trem4x - 5;
         }
         if(parametros->trem4x==90 && parametros->trem4y<=295){
             parametros->trem4y = parametros->trem4y - 5;
         }
        usleep(parametros->velocidade4);
    }

}

void MainWindow::comeca()
{
    sem_init(&sem436, 0, 2);
    sem_init(&sem6510, 0, 2);
    sem_init(&sem3, 0, 1);
    sem_init(&sem4, 0, 1);
    sem_init(&sem5, 0, 1);
    sem_init(&sem6, 0, 1);
    sem_init(&sem10, 0, 1);

    pthread_t thread1, thread2, thread3,thread4,thread5;
    pthread_create(&thread1, NULL, trem_1,(void*)this);
    pthread_create(&thread2, NULL, trem_2,(void*)this);
    pthread_create(&thread3, NULL, trem_3,(void*)this);
    pthread_create(&thread4, NULL, trem_4,(void*)this);
    pthread_create(&thread5, NULL, desenha,(void*)this);

    sem_destroy(&sem3);
    sem_destroy(&sem4);
    sem_destroy(&sem5);
    sem_destroy(&sem6);
    sem_destroy(&sem10);
    sem_destroy(&sem436);
    sem_destroy(&sem6510);
}

void MainWindow::atualiza_velocidade_verde()
{
    if(velocidade1>=6000){
        velocidade1 -= 6000;
    }
}
void MainWindow::diminui_velocidade_verde(){
    velocidade1 += 6000;
}

void MainWindow::atualiza_velocidade_vermelho()
{
    if(velocidade2>=6000){
        velocidade2 -=6000;
    }
}

void MainWindow::diminui_velocidade_vermelho(){
    velocidade2 += 6000;
}

void MainWindow::atualiza_velocidade_amarelo()
{
    if(velocidade3>=6000){
     velocidade3 -= 6000;
    }
}

void MainWindow::diminui_velocidade_amarelo(){
    velocidade3 += 6000;
}

void MainWindow::atualiza_velocidade_azul()
{
    if(velocidade4>=6000){
        velocidade4 -= 6000;
    }
}

void MainWindow::diminui_velocidade_azul(){
    velocidade4 += 6000;
}

