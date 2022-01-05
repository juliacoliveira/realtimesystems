#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPainter>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    virtual void paintEvent(QPaintEvent *event);
    int trem1x=110,trem1y=90;
    int trem2x=215,trem2y=90;
    int trem3x=320,trem3y=90;
    int trem4x=110,trem4y=295;
    long int velocidade1 = 60000;
    long int velocidade2 = 60000;
    long int velocidade3 = 60000;
    long int velocidade4 = 60000;
    Ui::MainWindow *ui;


private:

public slots:
    void comeca();
    void atualiza_velocidade_verde();
    void diminui_velocidade_verde();
    void atualiza_velocidade_amarelo();
    void diminui_velocidade_amarelo();
    void atualiza_velocidade_vermelho();
    void diminui_velocidade_vermelho();
    void atualiza_velocidade_azul();
    void diminui_velocidade_azul();
};

#endif // MAINWINDOW_H
