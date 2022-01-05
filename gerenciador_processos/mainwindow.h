#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
class QTimer;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    QString processo;
    int PID;
    int prioridade;
    int CPU;

public slots:
    void copiaTexto_processo();
    void copiaTexto_pid();
    void kill_processo();
    void stop_processo();
    void cont_processo();
    void copiaTexto_prioridade();
    void copiaTexto_cpu();
    void ler_processos();

private:
    Ui::MainWindow *ui;
    QTimer *m_timer;
};

#endif // MAINWINDOW_H
