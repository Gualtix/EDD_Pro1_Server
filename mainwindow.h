#ifndef MAINWINDOW_H
#define MAINWINDOW_H

//C++

//Qt
#include <QFile>
#include <QFileDialog>
#include <QMainWindow>
#include <QTcpServer>
#include <QTcpSocket>

//ADT
#include "jsonreader.h"
#include "sparsematrix.h"


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:

    void Nw_Connection();

    void socketReceive();

    void Star_Server();

    void Stop_Server();

    void SendMessage(QString msg);

    void on_btnServer_Start_clicked();

    void on_btnServer_Stop_clicked();

    void on_btnMatrix_Graph_clicked();

    void Load_Mattix();

    void Graph_Matrix();

    void Original();

    void Iniciado();

    void Apagado();

    void UpDate_Req(QString Req);

    void AddTableItem(int Rk,QString Usuario,QString Solicitud,QString Respuesta,QString Tiempo);

private:
    Ui::MainWindow *ui;

    SparseMatrix* Mtx;
    QTcpServer* mServer;
    QTcpSocket* mClient;
};

#endif // MAINWINDOW_H
