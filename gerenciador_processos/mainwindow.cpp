#include "mainwindow.h"
#include "ui_mainwindow.h"


#include  <time.h>
#include <iostream> // para: cout
#include <stdio.h>
#include <unistd.h>  // para: sleep()
#include <stdlib.h>
#include <math.h>
#include <signal.h>

#include <sys/time.h>     // getpriority(int which, int who)  setpriority(int which, int who, int prio);
#include <sys/resource.h>

#define _GNU_SOURCE
#include <sched.h>

#include <string.h>
#include <QDebug>
#include <QFile>
#include <QTextStream>
#include <QMessageBox>
#include <QTimer>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    m_timer = new QTimer(this);
    connect(m_timer,SIGNAL(timeout()),this,SLOT(copiaTexto_processo()));
    m_timer->start(1000);
    ui->processos_text_2->setVerticalScrollBar(ui->processos_text->verticalScrollBar());
    ui->processos_text_3->setVerticalScrollBar(ui->processos_text_2->verticalScrollBar());
    ui->processos_text_4->setVerticalScrollBar(ui->processos_text_3->verticalScrollBar());
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::copiaTexto_processo()
{
    processo=ui->pesquisar_text->toPlainText();
    if(processo==""){
        char parte1[100] = "ps -eo %u,%c,%C,%p";
        char parte2[] = " > saida2.txt";

        strcat(parte1,parte2);
        system(parte1);
        ler_processos();
    }
    else{
        char parte1[100] = "ps -eo %u,%c,%C,%p | grep ";
        char parte2[] = " > saida2.txt";

        //converter Qstring para char[]
        QByteArray ba = processo.toLocal8Bit();
        const char *c_str2 = ba.data();
        strcat(parte1,c_str2);
        strcat(parte1,parte2);
        system(parte1);
        ler_processos();
    }
}

void MainWindow::copiaTexto_pid()
{
    QString pid= ui->pid_text->toPlainText();
    PID = pid.toInt();
}

void MainWindow::kill_processo()
{
    copiaTexto_pid();
    kill(PID,9);
}

void MainWindow::stop_processo()
{
    copiaTexto_pid();
    kill(PID,SIGSTOP);
}

void MainWindow::cont_processo()
{
    copiaTexto_pid();
    kill(PID,SIGCONT);
}


void MainWindow::copiaTexto_prioridade()
{
    QString prio = ui->prioridade_text->toPlainText();
    prioridade = prio.toInt();
    copiaTexto_pid();
    setpriority(PRIO_PROCESS,PID,prioridade);
}

void MainWindow::copiaTexto_cpu()
{
   QString cpu = ui->cpu_text->toPlainText();
   CPU = cpu.toInt();

   cpu_set_t  mask;
   CPU_ZERO(&mask);
   CPU_SET(CPU, &mask);
   copiaTexto_pid();
   sched_setaffinity(PID, sizeof(mask), &mask);
}

void MainWindow::ler_processos()
{
    QFile arquivo("./saida2.txt");
    if(!arquivo.open(QFile::ReadOnly|QFile::Text)){
        QMessageBox::warning(this,"ERRO","Erro ao abri arquivo");
    }
    QTextStream entrada(&arquivo);
    QString texto;
    QString texto1;
    QString texto2;
    QString texto3;
    while(!entrada.atEnd()){
        QString aux =entrada.readLine();
        QStringList list1 = aux.split(',');
        texto+=list1[0]+"\n";
        texto1+=list1[1]+"\n";
        texto2+=list1[2]+"\n";
        texto3+=list1[3]+"\n";
    }
    ui->processos_text->setPlainText(texto);
    ui->processos_text_2->setPlainText(texto1);
    ui->processos_text_3->setPlainText(texto2);
    ui->processos_text_4->setPlainText(texto3);
    arquivo.close();
}
